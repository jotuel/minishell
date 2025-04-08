/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:32:26 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/07 22:47:54 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* returns 1 for match, 0 for no match.
*/
int	match_env_argument(t_char *source, char *env_var)
{
	int	i;

	i = 0;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if ((ft_isalnum(source[1].c) == 0 && ft_isspace(source[1].c) == 0
			&& source[1].c != '?'))
	{
		source[0].esc = 1;
		return (0);
	}
	i = 1;
	while (env_var[i - 1] && source[i].c && source[i].c == env_var[i - 1]
		&& source[i].var)
		i++;
	if (source[i].var == 0 && env_var[i - 1] == '=')
		return (1);
	return (0);
}

// returns a pointer to the start of env variable if you have the
const char	*ft_get_env(const char *target)
{
	if (target == NULL)
		return (NULL);
	while (*target && *target != '=')
		target++;
	if (*target == '=')
		target++;
	return (target);
}

// export finds all, ENV only finds if there is =
const char	*find_env(t_char *source, t_data *data)
{
	int	i;

	i = 0;
	while (i < ENV_SIZE)
	{
		if (match_env_argument(source, data->env[i]))
			return (ft_get_env(data->env[i]));
		i++;
	}
	return (NULL);
}

// Our env is not supposed to take arguments so dicard or error?
void	bi_env(t_data *data, int fd)
{
	const char	*str;
	int			i;

	i = 0;
	str = NULL;
	while (i < ENV_SIZE)
	{
		str = (data->env[i]);
		if (str && str[0] && str[0] != '?')
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
		i++;
	}
	fd = file_closer(fd);
}

/*
** keeps env variables up to date between commands
*/
void	update_env(int value, char *cmd, bool update)
{
	add_envvar(get_data()->env, "?", ft_itoa(value));
	if (update)
		add_envvar(get_data()->env, "_", cmd);
}
