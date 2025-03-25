/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:27:03 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/22 19:07:41 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//jos seuraava ei ole alnum eika _ eika "" eika '' eika ?

int	next_is_delim(char *str, int i, t_char *dst, int k)
{
	if (dst[k - 1].added)
		return (0);
	if (i != 0 && dst[k - 1].c != ' ' && dst[k - 1].esc != 0)
	{
		return (0);
	}
	i += 2;
	while (str[i] != 0 && str[i] != ' ')
	{
		if (str[i] == '\'' && str[i] == '\'')
		{
			i += 2;
		}
		else if (str[i] == '\"' && str[i] == '\"')
			i += 2;
		else
			return (0);
	}
	return (1);
}
//need a specific test for pipe

int	mark_redir(char *src, int *i, t_char *dst, int *k)
{
	if (src[*i] == src[(*i) + 1] && (src[*i] == '>' || src[*i] == '<'))
	{
		dst[*k].c = ' ';
		(*k)++;
		dst[*k].c = src[*i];
		(*k)++;
		(*i)++;
		dst[*k].c = src[*i];
		(*k)++;
		dst[*k].c = ' ';
		(*k)++;
		return (1);
	}
	else if (src[(*i) + 1] != src[*i] && (src[*i] == '>' || \
	src[*i] == '<' || src[*i] == '|' ))
	{
		dst[*k].c = ' ';
		(*k)++;
		dst[*k].c = src[*i];
		(*k)++;
		dst[*k].c = ' ';
		(*k)++;
		return (1);
	}
	return (0);
}

// i and k are set to zero
void	remove_quotes(t_char *dst, char *src, int i, int k)
{
	int	in_s_quotes;
	int	in_d_quotes;
	int	exp;

	in_s_quotes = 0;
	in_d_quotes = 0;
	exp = 0;
	while (src && src[i])
	{
		if (in_s_quotes)
			in_s_quotes = handle_s_quotes(src, dst, i, &k);
		else if (in_d_quotes)
			in_d_quotes = handle_d_quotes(src + i, dst, &k, &exp);
		else if (check_emp_arg(src, i, dst, &k))
			i++;
		else if (src[i] == '\"')
			in_d_quotes = 1;
		else if (mark_redir(src, &i, dst, &k) == 0)
			in_s_quotes = handle_rest(src, dst, i, &k);
		i++;
	}
	dst[k].c = '\0';
	if (in_d_quotes || in_s_quotes)
		error_printf("user", "quotes need to be closed");
}

// I will later refactor to remove the i and just pass the pointer to (src + i);
int	check_emp_arg(char *src, int i, t_char *dst, int *k)
{
	if (src[i] == '\'' && src[i + 1] == '\'' && next_is_delim(src, i, dst, *k))
	{
		dst[*k].ghost = 1;
		dst[*k].c = 'G';
		dst[*k + 1].c = ' ';
		dst[*k + 1].added = 1;
		*k += 2;
		return (1);
	}
	else if (src[i] == '\"' && src[i + 1] == '\"' && next_is_delim(src, i, dst,
			*k))
	{
		dst[*k].ghost = 1;
		dst[*k].c = 'G';
		dst[*k + 1].c = ' ';
		dst[*k + 1].added = 1;
		*k += 2;
		return (1);
	}
	return (0);
}
