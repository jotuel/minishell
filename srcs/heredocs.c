/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:18:56 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/08 18:19:02 by jrimpila         ###   ########.fr       */
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

static char	*return_result(char *result, int expand)
{
	if (result == NULL)
		result = ft_strdup("");
	if (expand)
		return (expand_heredocs(result));
	return (result);
}

/*
 * strjoin_wrapper - wrapper for ft_strjoin that frees the first string
 * @s1: first string to join
 * @s2: second string to join
 *
 * Return: pointer to the joined string
 */
static char	*strjoin_wrapper(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

// If expand is 1, expansion happens
char	*create_heredoc(char *terminat, int expand, char *result, char *tmp)
{
	char	*prompt;

	prompt = ft_strjoin(terminat, ">");
	while (tmp == NULL || ft_strncmp(terminat, tmp, ft_strlen(terminat) + 1))
	{
		if (tmp)
		{
			tmp = strjoin_wrapper(tmp, "\n");
			if (result)
			{
				result = strjoin_wrapper(result, tmp);
				free(tmp);
				tmp = NULL;
			}
			else
				result = tmp;
		}
		tmp = readline(prompt);
		if (!tmp)
		{
			if(RL_ISSTATE(RL_STATE_DONE))
				printf("%s: %s: %s at line %d %s (wanted `%s`)\n",
				SHELL, WARN, DOC, __LINE__, DELIM, terminat);
			break ;
		}
	}
	return (free(prompt), free(tmp), return_result(result, expand));
}
