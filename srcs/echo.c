/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:37:53 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/01 16:51:30 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo_check_opt(char *str)
{
	int	i;
	int	is_valid;

	i = 0;
	is_valid = 0;
	if (str[i] != '-')
		return (is_valid);
	i++;
	while (str[i])
	{
		if (str[i] == 'n')
		{
			is_valid = 1;
			i++;
		}
		else
		{
			is_valid = 0;
			return (is_valid);
		}
	}
	return (is_valid);
}

int	bi_echo(int argc, char *argv[], int fd)
{
	int	i;
	int	opt;

	opt = 0;
	if (argc > 1)
		opt = echo_check_opt(argv[1]);
	i = opt + 1;
	while (opt && i < argc && echo_check_opt(argv[i]))
		i++;
	while (i < argc)
	{
		write(fd, argv[i], ft_strlen(argv[i]));
		i++;
		if (i < argc)
			write(fd, " ", 1);
	}
	if (!opt)
		write(fd, "\n", 1);
	fd = file_closer(fd);
	return (0);
}
