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
	int	isvalid;

	i = 0;
	isvalid = 0;
	if (str[i] != '-')
		return (isvalid);
	i++;
	while (str[i])
	{
		if (str[i] == 'n')
		{
			isvalid = 1;
			i++;
		}
		else
		{
			isvalid = 0;
			return (isvalid);
		}
	}
	return (isvalid);
}

int	bi_echo(int argc, char *argv[], int fd)
{
	int	i;
	int	opt;

	opt = 0;
	if (argc > 1)
		opt = echo_check_opt(argv[1]);
	i = opt + 1;
	while (opt && echo_check_opt(argv[i]) && i < argc)
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
