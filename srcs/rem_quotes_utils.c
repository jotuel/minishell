/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:43:34 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 12:40:00 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_s_quotes(char *src, t_char *dst, int i, int *k)
{
	if (src[i] == '\'')
		return (0);
	else
	{
		dst[*k].c = src[i];
		dst[*k].esc = 1;
		(*k)++;
		return (1);
	}
}

int	handle_d_quotes(char *src, t_char *dst, int *k, int *exp)
{
	if (*src == '\"')
	{
		if (*exp == 1)
			*exp = 0;
		dst[*k + 1].blok = 1;
		return (0);
	}
	else
	{
		dst[*k].c = *src;
		if (*src == '$')
			*exp = 1;
		else if (*exp == 1)
		{
			if (ft_isalnum(*src) == 0 && *src != '_' && *src != '?')
			{
				*exp = 0;
				dst[*k + 1].blok = 1;
			}
		}
		if (*exp == 0 && *src)
			dst[*k].esc = 1;
		(*k)++;
		return (1);
	}
}

int	handle_rest(char *src, t_char *dst, int i, int *k)
{
	if (src[i] == '\'')
	{
		dst[(*k) + 1].blok = 1;
		return (1);
	}
	else if (src[i] == '$' && !ft_isalnum(src[i + 1]) && src[i + 1] != \
	'\'' && src[i + 1] != '\"' && src[i + 1] != '_' && src[i + 1] != '?')
	{
		dst[*k].c = src[i];
		dst[*k].esc = 1;
		(*k)++;
	}
	else
	{
		dst[*k].c = src[i];
		(*k)++;
	}
	return (0);
}
