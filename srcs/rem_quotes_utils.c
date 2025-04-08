/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:43:34 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/08 18:25:24 by jrimpila         ###   ########.fr       */
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

int	handle_tilde(char *src, t_char *dst, int i, int *k)
{
	int	j;

	if ((i == 0 || ft_isspace(src[i - 1])) && src[i] == '~' && (ft_isspace \
	(src[i + 1]) || src[i + 1] == '/' || src[i + 1] == '\0'))
	{
		j = 0;
		if (ret_ptr_to_envval("$HOME", get_data()) && ret_ptr_to_envval \
		("$HOME", get_data())[4])
		{
			while ("$HOME"[j])
			{
				dst[*k].c = "$HOME"[j];
				(*k)++;
				j++;
			}
			return (1);
		}
		while (HOME[j])
		{
			dst[*k].c = HOME[j++];
			(*k)++;
		}
		return (1);
	}
	return (0);
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
	else if (handle_tilde(src, dst, i, k))
		;
	else
	{
		dst[*k].c = src[i];
		(*k)++;
	}
	return (0);
}
