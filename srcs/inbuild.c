/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/26 18:31:15 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_redirections(t_sent *sent)
{
	int	fd;
	int	i;

	fd = 1;
	i = 0;
	while (sent->redirs[i].path)
	{
		if (sent->redirs[i].type == OUT_FILE)
			fd = open(sent->redirs[i].path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (sent->redirs[i].type == APPEND)
			fd = open(sent->redirs[i].path, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (sent->redirs[i].type == HERE_DOCS)
			fd = sent->redirs[i].here_fd;
		if (fd == -1)
			return (error_printf("open", strerror(errno)), 1);
		if (dup2(fd, 255) == -1)
			return (error_printf("dup2", strerror(errno)), 1);
		close(fd);
		fd = 255;
		i++;
	}
	return (fd);
}

// Cant handle redirection support currently
int	run_builtin(int argc, char *argv[], t_sent *sent, bool update)
{
    update_env(store_return_value(0, false), argv[0], update);
	if (!sent->inpipe && !sent->outpipe)
	   update = true;
	else
	   update = false;
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3) == 0)
		bi_cd(argc, argv, sent, do_redirections(sent));
	else if (ft_strncmp("pwd", argv[0], 4) == 0)
		bi_pwd(do_redirections(sent));
	else if (ft_strncmp("echo", argv[0], 5) == 0)
		bi_echo(argc, argv, do_redirections(sent));
	else if (ft_strncmp("env", argv[0], 4) == 0)
		bi_env(get_data(), do_redirections(sent));
	else if (ft_strncmp("export", argv[0], 7) == 0)
		bi_export(argc, argv, sent, do_redirections(sent));
	else if (ft_strncmp("unset", argv[0], 6) == 0)
		bi_unset(argc, argv, sent, do_redirections(sent));
	else if (ft_strncmp("exit", argv[0], 5) == 0)
		bi_exit(argc, argv, sent);
	else if (1)
		return (0);
	return (1);
}

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
	return (0);
}
