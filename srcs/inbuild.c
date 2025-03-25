/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/22 19:05:14 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Cant handle redirection support currently
int	run_builtin(int argc, char *argv[], t_sent *sent)
{
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3) == 0)
	{
		bi_cd(argc, argv, sent);
	}
	else if (ft_strncmp("pwd", argv[0], 4) == 0)
		bi_pwd();
	else if (ft_strncmp("echo", argv[0], 5) == 0)
		bi_echo(argc, argv);
	else if (ft_strncmp("env", argv[0], 4) == 0)
		bi_env(get_data());
	else if (ft_strncmp("export", argv[0], 7) == 0)
		bi_export(argc, argv, sent);
	else if (ft_strncmp("unset", argv[0], 6) == 0)
		bi_unset(argc, argv, sent);
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

//BASH version ignores arguments
int	bi_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		error_printf("system", "getcwd() error");
	return (0);
}
