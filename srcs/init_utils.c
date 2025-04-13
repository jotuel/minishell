/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:24:54 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/13 14:15:24 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_redirection(t_char *dst, int i)
{
	
}

static void check_amb_redir(t_char *dst, int i, const char *env, int env_i)
{
	int word_count;
	
	if (is_redirection(dst, i) == 0)
		return ;
	word_count = 0;
	while (env[env_i])
	{
		if (ft_isspace(env[env_i] == 0))
			word_count++;
		while (ft_isspace(env[env_i] == 0))
			env_i++;
		while (ft_isspace(env[env_i]))
			env_i++;
	}
	if (word_count == 0 || word_count > 1)
	{
		deallocate(get_data());
		store_return_value(1, true);
		
	}

}

int	copy_env_to_tchar(t_char *dst, int i, const char *env)
{
	int	env_i;

	if (env == NULL)
		return (i);
	env_i = 0;
	check_amb_redir(dst, i, env, 0);
	while (env[env_i])
	{
		dst[i].c = env[env_i];
		dst[i].var = 1;
		dst[i].esc = 0;
		dst[i].com = 0;
		dst[i].ghost = 0;
		dst[i].added = 0;
		i++;
		env_i++;
	}
	return (i);
}

char	**get_own_env(void)
{
	static char	*cpy[ENV_SIZE + 1];
	int			i;
	int			k;
	t_data		*data;

	data = get_data();
	i = 0;
	k = 0;
	ft_memset(cpy, 0, sizeof(cpy));
	while (k < ENV_SIZE)
	{
		if (data->env[k][0] != '\0')
		{
			cpy[i] = data->env[k];
			i++;
		}
		k++;
	}
	cpy[i] = NULL;
	return (cpy);
}

/*
** keeps the last executed programs return value
*/
int	store_return_value(int ret_val, bool add)
{
	static int	ret;

	if (add)
		ret = ret_val;
	return (ret);
}
