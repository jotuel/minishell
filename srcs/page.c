/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:15 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/22 19:05:54 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_file(t_token type)
{
	return (type == IN_FILE || type == OUT_FILE
		|| type == APPEND || type == HERE_DOCS
		|| type == HERE_QUOTE);
}

// i is 0, k is 0, sentence is calloced, node is pulled from data
t_sent	*conv_linked_to_sentence(int i, int k, t_node *node, t_sent *sentence);

static t_node	*check_inpipe(t_sent *sentence, t_node *node)
{
	if (node && node->type == PIPE)
	{
		sentence->inpipe = 1;
		if (get_data()->tokens.last == node || node->next->type == PIPE)
			ft_exit(get_data(), "syntax error near token", "|", 1);
		node = destroy_node(&get_data()->tokens, node);
	}
	return (node);
}

// i is 0, k is 0, sentence is calloced, node is pulled from data
t_sent	*conv_linked_to_sentence(int i, int k, t_node *node, t_sent *sentence)
{
	node = check_inpipe(sentence, node);
	while (node)
	{
		node = get_data()->tokens.first;
		if (node->type == PIPE)
		{
			sentence->argc = i;
			sentence->outpipe = 1;
			return (sentence);
		}
		if (node->type == REDIRECT)
		{
			if (node->next->type == REDIRECT || node->next->type == PIPE
				|| get_data()->tokens.last == node)
				ft_exit(get_data(), "syntax error near \
				unexpected token", "nl", 1);
		}
		else if (is_file(node->type))
			add_redirection(node, sentence, k++);
		else
			sentence->array[i++] = cnvrt_to_char(node->str);
		node = destroy_node(&get_data()->tokens, node);
	}
	sentence->argc = i;
	return (sentence);
}

void	destroy_old_page(void)
{
	int		i;
	int		k;
	t_data	*data;

	data = get_data();
	i = 0;
	while (i < MAX_SENTENCES)
	{
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

	destroy_old_page();
	page = get_data()->page;
	if (stack == NULL || stack->first == NULL)
		return (NULL);
	cur = stack->first;
	i = 0;
	while (cur)
	{
		page[i] = conv_linked_to_sentence(0, 0, get_data()->tokens.first,
				ft_xcalloc(sizeof(t_sent), 1));
		cur = stack->first;
		i++;
	}
	return (page);
}
