/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/03 09:46:01 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**  if none fd is returned as it is passed and if any open is dupped to 255
**  which gets returned.
*/
int	do_redirections(t_sent *sent, int fd, int i)
{
	while (sent->redirs[i].path)
	{
		if (sent->redirs[i].type == OUT_FILE)
			fd = open(sent->redirs[i].path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (sent->redirs[i].type == APPEND)
			fd = open(sent->redirs[i].path, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (sent->redirs[i].type == HERE_DOCS)
			fd = sent->redirs[i].here_fd;
		if (fd == -1 || dup2(fd, 255) == -1)
		{
			error_printf(sent->redirs[i].path, strerror(errno));
			free(sent->redirs[i].path);
			sent->redirs[i].path = NULL;
			return (1);
		}
		close(fd);
		free(sent->redirs[i].path);
		sent->redirs[i].path = NULL;
		fd = 255;
		i++;
	}
	return (fd);
}

/*
** updates env, runs built in if is one and redirects if needed ultimately
** storing the return value and freeing all the necessary bits.
*/
int	run_builtin(int argc, char *argv[], t_sent *sent, bool update)
{
	update_env(store_return_value(0, false), argv[0], update);
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3) == 0)
		argc = bi_cd(argc, argv, sent);
	else if (ft_strncmp("pwd", argv[0], 4) == 0)
		argc = bi_pwd(do_redirections(sent, 0, 1));
	else if (ft_strncmp("echo", argv[0], 5) == 0)
		argc = bi_echo(argc, argv, do_redirections(sent, 0, 1));
	else if (ft_strncmp("env", argv[0], 4) == 0)
		bi_env(get_data(), do_redirections(sent, 0, 1));
	else if (ft_strncmp("export", argv[0], 7) == 0)
		argc = bi_export(argc, argv, sent, do_redirections(sent, 0, 1));
	else if (ft_strncmp("unset", argv[0], 6) == 0)
		argc = bi_unset(argc, argv, sent);
	else if (ft_strncmp("exit", argv[0], 5) == 0)
		argc = bi_exit(argc, argv, sent);
	else
		return (deallocate(get_data()), 0);
	store_return_value(argc, true);
	return (deallocate(get_data()), 1);
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

// BASH version ignores arguments
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
