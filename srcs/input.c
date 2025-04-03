/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:11:31 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/02 17:59:20 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** this functions purpose is beyond me.
*/
int	cwd(t_data *data)
{
	getcwd(data->cwd, sizeof(data->cwd));
	return (0);
}

/*
** tokenises cmd and parses it.
*/
static void	process(char *line, t_data *data, t_char *result)
{
	result = lexify(line, data);
	free(result);
	result = NULL;
	create_page(&data->tokens);
}

/*
**  it's from the readline manuals but extented (a bit)
**
**  mostly more flashy color and some emoji too.
*/
static char	*rl_gets(t_data *data)
{
	static char	*line = NULL;
	static char	*strcwd;
	static char	*tmp;

	cwd(data);
	tmp = ft_strjoin(GREEN USER ":" RESET, data->cwd);
	strcwd = ft_strjoin(tmp, BRIGHT_YELLOW "😎>" RESET);
	free(tmp);
	tmp = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(strcwd);
	free(strcwd);
	strcwd = NULL;
	if (line && all_isspace(line))
		line[0] = '\0';
	if (line && *line)
		add_history(line);
	update_env(store_return_value(0, false), NULL, false);
	return (line);
}

/*
** in interactive mode called in a loop to get some user input.
**
** otherwise handles the input given and returns.
*/
int	prompt_input(char *line, int pfd[2], t_data *data, int input)
{
	set_signals();
	if (input == 0)
		line = rl_gets(data);
	if (line == NULL)
		return (1);
	else if (line[0] == '\0')
		return (0);
	process(line, data, NULL);
	if (data->page[0] && !data->page[0]->outpipe && !data->page[0]->inpipe
		&& is_builtin(data->page[0]->array[0]))
		run_builtin(data->page[0]->argc, data->page[0]->array, data->page[0],
			true);
	else if (data->page[0])
	{
		util_parse_args(data, 0);
		block_signals_in_parent();
		if (-1 == pipe(pfd))
			ft_exit(data, "pipe", strerror(errno), errno);
		store_return_value(execute(data->page[0], pfd, 1, data), true);
	}
	return (0);
}
