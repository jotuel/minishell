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

/*
* Closes the given file descriptor if it is greater than 2.
*/
void	pipe_closer(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

/*
* Checks if the given character is a question mark or an underscore.
* Returns 1 if the character is a question mark or an underscore, 0 otherwise.
*/
int	question_or_underscore(char const c)
{
	return (c == '?' || c == '_');
}

/*
* Checks if the given file name is a valid input file.
* Returns 0 if the file exists and is readable, -1 otherwise.
*/
int	infile_checker(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (-1 == fd)
		return (-1);
	if (-1 == dup2(fd, 255))
		return (-1);
	close(fd);
	return (0);
}
