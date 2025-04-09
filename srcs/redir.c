/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:39:47 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 12:14:01 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_here_expansion(t_char *str)
{
	int	i;

	i = 0;
	while (str[i].c)
	{
		if (str[i].esc || str[i].blok)
			return (1);
		i++;
	}
	return (0);
}

void	add_redirection(t_node *node, t_sent *sentence, int i)
{
	if (node->type == HERE_DOCS && (check_here_expansion(node->str)))
		sentence->redirs[i].type = HERE_QUOTE;
	else
		sentence->redirs[i].type = node->type;
	if (sentence->redirs[i].type == HERE_DOCS)
		sentence->redirs[i].here_fd = open_temp_heredocs(node, 1, NULL, NULL);
	else if (sentence->redirs[i].type == HERE_QUOTE)
		sentence->redirs[i].here_fd = open_temp_heredocs(node, 0, NULL, NULL);
	else if (node->str)
		sentence->redirs[i].path = cnvrt_to_char(node->str);
	else
	{
		deallocate(get_data());
		error_printf("", "syntax error near unexpected token `newline'");
		store_return_value(2, true);
		return ;
	}
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		deallocate(get_data());
		store_return_value(2, true);
		return ;
	}
}
