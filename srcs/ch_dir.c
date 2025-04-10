/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:39:31 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/10 10:55:33 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Only takes 1 argument, throws error otherwise
static int	is_valid_cd(const char *dir)
{
	struct stat	file_stat;

	if (dir == NULL)
		dir = find_env_value("$HOME", get_data());
	if (dir == NULL)
		return (printf("minishell: cd: HOME not set\n"), 0);
	if (dir[0] == 0)
		return (1);
	if (stat(dir, &file_stat) == -1)
	{
		if (errno == ENOENT)
			error_printf("cd", "No such file or directory");
		else if (errno == EACCES)
			error_printf("cd", "permission denied");
		else
			error_printf("cd", "unknown stat error");
		return (0);
	}
	if (!S_ISDIR(file_stat.st_mode) && !S_ISLNK(file_stat.st_mode))
		return (error_printf("cd", "not a directory"), 0);
	if (access(dir, X_OK))
		return (error_printf("cd", "permission denied"), 0);
	return (1);
}

int	bi_cd(int argc, char *argv[], t_sent *sent)
{
	char	*cur;
	char	cwd[PATH_MAX];

	if (argc > 2)
	{
		error_printf("cd", "too many arguments\n");
		return (1);
	}
	cur = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (is_valid_cd(argv[1]) && !sent->inpipe && !sent->outpipe)
		add_envvar(get_data()->env, "OLDPWD", getcwd(cwd, PATH_MAX));
	else
	{
		free(cur);
		return (1);
	}
	if (argv[1] == NULL)
		chdir(find_env_value("$HOME", get_data()));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(find_env_value("$OLDPWD", get_data()));
	else
		chdir(argv[1]);
	add_envvar(get_data()->env, "PWD", getcwd(cwd, PATH_MAX));
	return (free(cur), 0);
}
