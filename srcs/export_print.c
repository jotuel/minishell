/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:29:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/01 17:00:42 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sort_cpy(char **cpy);
static void	final_print(char **env, int i, int fd);

// Creates an array of pointers that are later sorted and printed
int	print_alphabetically(char env[ENV_SIZE + 1][MAX_LENGTH + 1], int fd)
{
	char	*cpy[ENV_SIZE + 1];
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (k < ENV_SIZE)
	{
		if (env[k][0] != '\0')
		{
			cpy[i] = env[k];
			i++;
		}
		k++;
	}
	cpy[i] = NULL;
	sort_cpy(cpy);
	final_print(cpy, 0, fd);
	fd = file_closer(fd);
	return (0);
}

static void	sort_cpy(char **cpy)
{
	int		i;
	char	*tmp;
	int		k;

	k = 0;
	while (k < ENV_SIZE && cpy[k])
	{
		i = 0;
		while (i < ENV_SIZE && cpy[i])
		{
			if (cpy[i + 1] && ft_strncmp(cpy[i], cpy[i + 1], MAX_LENGTH) > 0)
			{
				tmp = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp;
			}
			i++;
		}
		k++;
	}
}

// Prints the variables in the format desired by export
// int i gets passed as zero to appease norminette
static void	final_print(char **env, int i, int fd)
{
	int	k;

	while (i < ENV_SIZE && env[i])
	{
		k = 0;
		if (ft_strchr(env[i], '=') && (ft_strncmp(env[i], "_=", 2) != 0)
			&& env[i][0] != '?')
		{
			write(fd, "declare -x ", 11);
			while (env[i][k] && env[i][k] != '=')
			{
				write(fd, &env[i][k], 1);
				k++;
			}
			k++;
			if (env[i][k])
			{
				write(fd, "=\"", 2);
				while (env[i][k])
				{
					write(fd, &env[i][k], 1);
					k++;
				}
				write(fd, "\"", 1);
			}
			write(fd, "\n", 1);
		}
		i++;
	}
}
