/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:24:54 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/06 17:32:25 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	copy_env_to_tchar(t_char *dst, int i, const char *env)
{
	int	env_i;

	if (env == NULL)
		return (i);
	env_i = 0;
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

char **get_own_env(void)
{
    static char *cpy[ENV_SIZE + 1];
    int i;
	int	k;
	t_data *data;

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
    return cpy;
}
