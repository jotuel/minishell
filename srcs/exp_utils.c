/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/08 13:29:31 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	match_env_argument_char(char *source, char *env_var)
{
	int	i;

	i = 1;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if ((ft_isalnum(source[i]) == 0 && source[i] != '_' && source[i] != '?'))
		return (0);
	while (ft_isalnum(source[i]) || source[i] == '_' || source[i] == '?')
	{
		if (source[i] == env_var[i - 1])
			i++;
		else
			break ;
	}
	if ((env_var[i - 1] == 0 || env_var[i - 1] == '=')
		&& !ft_isalnum(source[i]) && source[i] != '_' && source[i] != '?')
		return (1);
	return (0);
}

static const char	*ret_ptrr_to_envval(char *source, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->env_count)
	{
		if (match_env_argument_char(source, data->env[i]))
			return (((const char *)data->env[i]));
		i++;
	}
	return (NULL);
}

const char	*find_env_value(char *source, t_data *data)
{
	int			i;
	const char	*ptr;

	i = 0;
	ptr = ret_ptrr_to_envval(source, data);
	if (ptr)
	{
		while (ptr[i] && ptr[i] != '=')
			i++;
	}
	if (ptr && ptr[i] == '=')
	{
		i++;
	}
	if (ptr)
		return (ptr + i);
	return (NULL);
}

/*
**This is the main expansion function
*/
void	expand_envvar(char *unexp, char *exp, int *i, int *k)
{
	const char	*ptr_envvar;
	int			j;

	ptr_envvar = ret_ptrr_to_envval(unexp + *i, get_data());
	j = 0;
	while (ptr_envvar && ptr_envvar[j] && ptr_envvar[j] != '=')
		j++;
	if (ptr_envvar && ptr_envvar[j] == '=')
		j++;
	while (ptr_envvar && ptr_envvar[j])
	{
		exp[*k] = ptr_envvar[j];
		(*k)++;
		j++;
	}
	if (unexp[*i] == '$')
		(*i)++;
	else
		error_printf("DEBUG", "something seems wrong");
	while (ft_isalnum(unexp[*i]) || unexp[*i] == '_')
		(*i)++;
}
