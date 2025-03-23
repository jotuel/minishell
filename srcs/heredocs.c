/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:18:56 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/23 12:24:28 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_heredocs(char *unexpanded)
{
	int		i;
	int		k;
	char	*expanded;

	i = 0;
	k = 0;
	expanded = ft_xcalloc(65000, 1);
	while (unexpanded[i])
	{
		if (unexpanded[i] == '$')
		{
			expand_envvar(unexpanded, expanded, &i, &k);
		}
		expanded[k] = unexpanded[i];
		i++;
		k++;
	}
	free(unexpanded);
	return (expanded);
}

int	t_compare(t_char *str, char *str2)
{
	int	i;

	if (!str)
		perror("Heredocs delimiter should not be NULL\n");
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

static char	*return_result(char *result, int expand)
{
	if (result == NULL)
		result = ft_strdup("");
	if (expand)
		return (expand_heredocs(result));
	return (result);
}

//If expand is 1, expansion happens
char	*create_heredoc(char *terminator, int expand, char *result, char *tmp)
{
	while (tmp == NULL || ft_strncmp(terminator, tmp, ft_strlen(terminator
				+ 1)))
	{
		if (tmp)
		{
			tmp = ft_strjoin(tmp, "\n");
			if (result)
			{
				result = ft_strjoin(result, tmp);
				free(tmp);
				tmp = NULL;
			}
			else
				result = tmp;
		}
		tmp = readline(">");
		if (!tmp)
		{
			error_printf("warning", "here-document limited by end-of-file");
			break ;
		}
	}
	free(tmp);
	return (return_result(result, expand));
}
