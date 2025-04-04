/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:15 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/04 12:52:43 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_file(t_token type)
{
	return (type == IN_FILE || type == OUT_FILE || type == APPEND
		|| type == HERE_DOCS || type == HERE_QUOTE);
}

static t_node	*check_inpipe(t_sent **sentence, t_node *node)
{
	t_data	*data;

	data = get_data();
	if (node && node->type == PIPE)
	{
		(*sentence)->inpipe = 1;
		if (data && (data->tokens.last == node || node->next->type == PIPE))
			return ((t_node *)syntax_error("|"));
		node = destroy_node(&get_data()->tokens, node);
	}
	return (node);
}

// i is 0, k is 0, sentence is calloced, node is pulled from data
t_sent	*conv_linked_to_sentence(int i, int k, t_node *node, int nbr)
{
	node = check_inpipe(&get_data()->page[nbr], node);
	while (node)
	{
		node = get_data()->tokens.first;
		if (node->type == PIPE)
		{
			get_data()->page[nbr]->argc = i;
			get_data()->page[nbr]->outpipe = 1;
			return (get_data()->page[nbr]);
		}
		if (node->type == REDIRECT)
		{
			if (node->next->type == REDIRECT || node->next->type == PIPE
				|| get_data()->tokens.last == node)
				return (syntax_error("`newline'"));
		}
		else if (is_file(node->type))
			add_redirection(node, get_data()->page[nbr], k++);
		else
			get_data()->page[nbr]->array[i++] = cnvrt_to_char(node->str);
		node = destroy_node(&get_data()->tokens, node);
	}
	if (get_data()->page[nbr])
		get_data()->page[nbr]->argc = i;
	return (get_data()->page[nbr]);
}

void	destroy_old_page(int i, int j, int k, t_data *data)
{
	data = get_data();
	while (i < MAX_SENTENCES)
	{
		j = 0;
		while (data->page[i] && data->page[i]->redirs[j].path)
		{
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
	i = 0;
	while (cur)
	{
		page[i] = ft_xcalloc(sizeof(t_sent), 1);
		conv_linked_to_sentence(0, 0, get_data()->tokens.first, i);
		if (!page[i])
			return (destroy_old_page(i, 0, 0, get_data()), NULL);
		cur = stack->first;
		i++;
	}
	return (page);
}
