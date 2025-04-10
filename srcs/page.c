/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:15 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/10 13:35:01 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_file(t_token type)
{
	return (type == IN_FILE || type == OUT_FILE || type == APPEND
		|| type == HERE_DOCS || type == HERE_QUOTE);
}

static t_node	*check_inpipe(int nbr, t_node *node)
{
	t_data	*data;

	data = get_data();
	if (node && node->type == PIPE)
	{
		data->page[nbr]->inpipe = 1;
		node = destroy_node(&data->tokens, node);
	}
	return (node);
}

// i is 0, k is 0, sentence is calloced, node is pulled from data
t_sent	*conv_linked_to_sentence(int i, int k, t_node *node, t_sent **sent)
{
	while (node)
	{
		node = get_data()->tokens.first;
		if (node && node->type == PIPE)
		{
			(*sent)->outpipe = 1;
			if (get_data()->tokens.last == node)
				get_more_input();
			break ;
		}
		if (node && node->type == REDIRECT)
		{
			if (node->next->type == REDIRECT || node->next->type == PIPE)
				return (syntax_error(node));
		}
		else if (node && is_file(node->type))
			add_redirection(node, *sent, k++);
		else if (node)
			(*sent)->array[i++] = cnvrt_to_char(node->str);
		if (get_data()->tokens.first && node)
			node = destroy_node(&get_data()->tokens, node);
	}
	if (*sent)
		(*sent)->argc = i;
	return (*sent);
}

void	destroy_old_page(int i, int j, int k, t_data *data)
{
	data = get_data();
	while (i < MAX_SENTENCES)
	{
		j = 0;
		while (data->page[i] && data->page[i]->redirs[j].path)
		{
			if (data->page[i]->redirs[j].here_fd > 2)
				close (data->page[i]->redirs[j].here_fd);
			free(data->page[i]->redirs[j].path);
			data->page[i]->redirs[j++].path = NULL;
		}
		k = 0;
		while (k < MAX_SENT_SIZE && data->page[i])
		{
			free(data->page[i]->array[k]);
			data->page[i]->array[k] = NULL;
			k++;
		}
		free(data->page[i]);
		data->page[i] = NULL;
		i++;
	}
	data->herecount = 0;
}

t_sent	**create_page(t_list *stack)
{
	t_sent	**page;
	t_node	*cur;
	int		i;

	destroy_old_page(0, 0, 0, get_data());
	page = get_data()->page;
	if (stack == NULL || stack->first == NULL)
		return (NULL);
	cur = stack->first;
	if (cur && cur->type == PIPE)
		return (syntax_error(cur), NULL);
	i = 0;
	while (cur)
	{
		page[i] = ft_xcalloc(sizeof(t_sent), 1);
		conv_linked_to_sentence(0, 0, check_inpipe(i, get_data()->tokens.first),
			&page[i]);
		if (!page[i])
			return (destroy_old_page(i, 0, 0, get_data()), NULL);
		cur = stack->first;
		i++;
	}
	return (page);
}
