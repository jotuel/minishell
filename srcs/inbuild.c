/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/10 10:57:39 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**  if none fd is returned as it is passed and if any open is dupped to 255
**  which gets returned.
*/
int	do_redirections(t_dir *red, int fd, int ir)
{
	while (red[ir].path)
	{
		if (red[ir].type == OUT_FILE)
			fd = open(red[ir].path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (red[ir].type == IN_FILE)
			if (infile_checker(red[ir++].path))
				return (error_printf(red[ir].path, strerror(errno)), -1);
		else
			continue ;
		else if (red[ir].type == APPEND)
			fd = open(red[ir].path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (red[ir].type == HERE_DOCS)
			fd = red[ir].here_fd;
		if (fd == -1 || file_has_error(red[ir].path, red[ir].type))
			return (error_printf(red[ir].path, strerror(errno)), -1);
		if (-1 == dup2(fd, 255))
			return (error_printf("dup2", strerror(errno)), -1);
		if (fd != 1)
			close(fd);
		else
			close(255);
		fd = 255;
		ir += 1;
	}
	return (fd);
}

/*
** updates env, runs built in if is one and redirects if needed ultimately
** storing the return value and freeing all the necessary bits.
*/
int	run_builtin(int argc, char *argv[], t_sent *sent, bool update)
{
	int	fd;

	update_env(store_return_value(0, false), argv[argc - 1], update);
	fd = do_redirections(sent->redirs, 1, 0);
	if (fd == -1)
		return (store_return_value(1, true));
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3) == 0)
		argc = bi_cd(argc, argv, sent);
	else if (ft_strncmp("pwd", argv[0], 4) == 0)
		argc = bi_pwd(fd);
	else if (ft_strncmp("echo", argv[0], 5) == 0)
		argc = bi_echo(argc, argv, fd);
	else if (ft_strncmp("env", argv[0], 4) == 0)
		bi_env(get_data(), fd);
	else if (ft_strncmp("export", argv[0], 7) == 0)
		argc = bi_export(argc, argv, sent, fd);
	else if (ft_strncmp("unset", argv[0], 6) == 0)
		argc = bi_unset(argc, argv, sent);
	else if (ft_strncmp("exit", argv[0], 5) == 0)
		argc = bi_exit(argc, argv, sent);
	store_return_value(argc, true);
	return (deallocate(get_data()), argc);
}

/*
**  returns a positive int value corresponding to a name of a built in
**  which funnily enough only ends up ever being used as a boolean so
**  this really could be rewriten as return logical or of all comparisons
**  but meh.
*/
int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (2);
	else if (ft_strncmp("echo", cmd, 5) == 0)
		return (3);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (4);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (5);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (6);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (7);
	return (0);
}

/*
**   We ignore any arguments
*/
int	bi_pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(fd, cwd, strlen(cwd));
		write(fd, "\n", 1);
	}
	else
	{
		error_printf("system", "getcwd() error");
	}
	fd = file_closer(fd);
	return (0);
}

/*
**   avoids closing stdout for no good reason and closes other files.
*/
int	file_closer(int fd)
{
	if (fd == 255)
		close(fd);
	return (1);
}
