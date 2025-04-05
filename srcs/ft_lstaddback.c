/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:41:58 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 19:09:32 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// BASH counts heredocs quite early so we do it while creating nodes
static void	set_type(t_node *new)
{
	if (new->str && new->str[0].c == '|' && new->str[0].com)
		new->type = PIPE;
	else if (((new->str && new->str[0].c == '>') || (new->str
				&& new->str[0].c == '<' && new->str[0].com)))
		new->type = REDIRECT;
	else if (new->prev->str && new->prev->str[0].c == '>'
		&& new->prev->str[1].c == '>' && new->prev->str[0].com)
		new->type = APPEND;
	else if (new->prev->str && new->prev->str[0].c == '>'
		&& new->prev->str[0].com)
		new->type = OUT_FILE;
	else if (new->prev->str && new->prev->str[0].c == '<'
		&& new->prev->str[1].c == '<' && new->prev->str[0].com)
	{
		new->type = HERE_DOCS;
		get_data()->herecount++;
		if (get_data()->herecount >= 17)
			ft_exit(get_data(), "Maximum amount of heredocs is 16", "", 2);
	}
	else if (new->prev->str && new->prev->str[0].c == '<'
		&& new->prev->str[0].com)
		new->type = IN_FILE;
	else
		new->type = ARG;
}

static void	add_back_utils(t_list *stack, t_node *new, t_node *cur)
{
	cur->next = new;
	stack->last = new;
}

static int	initialize_empty_stack(t_list *stack, t_node *new)
{
	stack->first = new;
	stack->last = new;
	new->next = new;
	new->prev = new;
	set_type(new);
	if (new->type == PIPE)
	{
		deallocate(get_data());
		store_return_value(2, true);
		return (error_printf("syntax error near", "unexpected token '|'"), 1);
	}
	return (0);
}
//returns 0 on success
int	ft_lstadd_back(t_list *stack, t_node *new)
{
	t_node	*cur;

	if (new == NULL)
		return (error_printf("list", "added to an empty list"), 1);
	if (stack->first == NULL)
		return (initialize_empty_stack(stack, new));
	cur = stack->first;
	if (stack->first == stack->last)
	{
		add_back_utils(stack, new, cur);
		cur->prev = new;
		new->prev = cur;
		new->next = cur;
		set_type(new);
		return (0);
	}
	while (cur != stack->last)
		cur = cur->next;
	add_back_utils(stack, new, cur);
	new->prev = cur;
	new->next = stack->first;
	stack->first->prev = stack->last;
	set_type(new);
	return (0);
}
