/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:25 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/08 15:37:52 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

void	init(char env_cpy[MAX_VARS + 1][MAX_LENGTH + 1], char **orig)
{
	int	i;

	i = 0;
	while (i < MAX_VARS && orig[i])
	{
		if (ft_strncmp(orig[i], "SHELL=", 6) == 0)
			ft_strlcpy(env_cpy[i], "SHELL=minishell", MAX_LENGTH);
		else if (ft_strncmp(orig[i], "_=", 2))
			ft_strlcpy(env_cpy[i], orig[i], MAX_LENGTH);
		i++;
	}
	get_data()->env_count = i;
}

int	main(int argc, char **argv, char *envp[])
{
	int	pfd[2];
	int	ret;

	if (argc > 2)
		return (-1);
	init(get_data()->env, envp);
	set_signals();
	ret = 0;

	if (argc == 2)
		ret = prompt_input(argv[1], pfd, get_data(), 1);
	while (!ret)
		ret = prompt_input(NULL, pfd, get_data(), 0);
	rl_clear_history();
	deallocate(get_data());
	return (store_return_value(0, false));
}
