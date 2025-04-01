/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:41:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/01 17:37:34 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	iterate_list(t_list *list, t_node_func func)
{
	t_node	*current;

	current = list->first;
	while (current && current != list->last)
	{
		func(list, current);
		current = current->next;
	}
	if (current && current == list->last)
	{
		func(list, current);
	}
}

// Destroys the current node and moves to the next node
t_node	*destroy_node(t_list *list, t_node *node)
{
	t_node	*cur;

	cur = node->next;
	if (list->first == node && list->last == node)
	{
		list->first = NULL;
		cur = NULL;
		list->last = NULL;
	}
	else if (list->first == node)
		list->first = node->next;
	else if (list->last == node)
		list->last = node->prev;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node->str);
	node->str = NULL;
	free(node);
	node = NULL;
	return (cur);
}

void	pipe_closer(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

int	question_or_underscore(char const c)
{
	return (c == '?' || c == '_');
}

size_t	ft_wrdlen(t_char *str, t_data *data)
{
	size_t	i;
	size_t	count_i;

	(void)data;
	i = 0;
	count_i = 0;
	if (str == NULL)
	{
		error_printf("system", "failure");
		return (-1);
	}
	while (str[i].c != 0 && (str[i].c != ' ' || str[i].esc == 1))
	{
		if (str[i].ghost == 0)
			count_i++;
		i++;
	}
	return (count_i);
}
