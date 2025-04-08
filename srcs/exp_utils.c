/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/08 17:17:28 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Expects the source with a $
static int	match_env_argument_char(char *source, char *env_var)
{
	int	i;

	i = 0;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if ((ft_isalnum(source[i]) == 0 && source[i] != '_' && source[i] != '?'))
		return (0);
	while (ft_isalnum(source[i]) || source[i] == '_' || source[i] == '?')
	{
		if (source[i] == env_var[i])
			i++;
		else
			break ;
	}
	if ((env_var[i] == 0 || env_var[i] == '=')
		&& !ft_isalnum(source[i]) && source[i] != '_' && source[i] != '?')
		return (1);
	return (0);
}

//expects the source with $
char	*ret_ptr_to_envval(char *source, t_data *data)
{
	int	i;
	int	k;

	k = 0;
	if (source[0] == '$')
		k = 1;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (match_env_argument_char(source + k, data->env[i]))
			return (((char *)data->env[i]));
		i++;
	}
	return (NULL);
}

const char	*find_env_value(char *source, t_data *data)
{
	int			i;
	const char	*ptr;

	i = 0;
	ptr = ret_ptr_to_envval(source, data);
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

	ptr_envvar = ret_ptr_to_envval(unexp + *i, get_data());
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

int	append_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *name, \
char *value)
{
	char	*ptr;
	int		i;
	int		k;

	if (name == NULL || name[0] == 0)
		return (1);
	ptr = ret_ptr_to_envval(name, get_data());
	if (ptr == NULL)
		return (add_envvar(env, name, value));
	i = 0;
	while (ptr[i])
	{
		i++;
	}
	k = 0;
	while (value && value[k] && i < MAX_LENGTH)
	{
		ptr[i] = value[k];
		i++;
		k++;
	}
	return (0);
}
