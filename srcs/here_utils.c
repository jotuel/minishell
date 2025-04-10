/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:30:52 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/10 18:07:34 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	t_compare(t_char *str, char *str2)
{
	int	i;

	if (!str)
		error_printf("debug", "heredoc delimiter should not be NULL");
	if (!str2)
		return (1);
	i = 0;
	while (str[i].c && str2[i])
	{
		if (str[i].c != str2[i])
			return (1);
		i++;
	}
	if (str[i].c != str2[i])
		return (1);
	return (0);
}

int	start_of_heredoc(t_char *str, int i)
{
	if (i >= 3 && ft_isspace(str[i].c) && !str[i].esc && str[i - 2].com \
	&& str[i - 2].c == '<' && str[i - 1].com && str[i - 1].c == '<')
	{
		return (1);
	}
	return (0);
}

int	end_of_heredoc(t_char *str, int i)
{
	if (str[i].esc)
		return (0);
	if (ft_isspace(str[i].c))
		return (1);
	return (0);
}
