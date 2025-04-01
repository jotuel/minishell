/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:21:45 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/27 14:11:55 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

bool		handle_redirection(char *sentence, enum e_token type, int fd);
static void	deal_with_sentence(t_sent *sentence, int i, int pfd[2], bool w[2]);

/*
 * all the forked subprocesses end up here, redirections are dealt with
 * and commands get executed.
 */
static void	execute_child(t_sent *sent, int pfd[2], pid_t child)
{
	if (!child)
	{
		unset_signals();
		deal_with_sentence(sent, 0, pfd, (bool[2]){0, 0});
		if (!sent->array[0])
			exit(0);
		if (is_builtin(sent->array[0]))
			exit(run_builtin(sent->argc,
					sent->array, sent, false));
		if (-1 == execve(sent->array[0], sent->array, __environ))
			ft_exit(get_data(), sent->array[0], strerror(errno), errno);
	}
	else if (child == -1)
		ft_exit(get_data(), "fork", strerror(errno), errno);
}

static int	wait_for_child(int ret, int state, pid_t last_child, int *i)
{
	while (*i)
	{
		if (last_child == waitpid(0, &state, 0))
			ret = state;
		(*i) -= 1;
	}
	deallocate(get_data());
	if (WIFSIGNALED(ret))
	   return (WTERMSIG(ret) + 128);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (EXIT_SUCCESS);
}

/*
** forks recursively as long as there are new commands
*/
int	execute(t_sent *sentence, int pfd[2], pid_t my_child, t_data *data)
{
	static int	i;

	if (my_child > 0 && data->page[i])
	{
		pipe_closer(&pfd[STDOUT_FILENO]);
		if (sentence->outpipe)
		{
			if (data->page[i - 1] && data->page[i - 1]->error > 2)
				pipe_closer(&data->page[i - 1]->error);
			data->page[i]->error = pfd[STDIN_FILENO];
			pipe(pfd);
		}
		return (execute(data->page[i++], pfd, fork(), data));
	}
	execute_child(sentence, pfd, my_child);
	pipe_closer(&pfd[STDIN_FILENO]);
	pipe_closer(&pfd[STDOUT_FILENO]);
	if (data->page[i - 1] && data->page[i - 1]->error > 2)
		pipe_closer(&data->page[i - 1]->error);
	return (wait_for_child(0, 0, my_child, &i));
}

/*
** take from sentence the out and infiles plus here docs and dup2 them to
** stdin or out.
*/
void	deal_with_sentence(t_sent *sentence, int i, int pfd[2], bool w[2])
{
	while (sentence->redirs[i].path || sentence->redirs[i].here_fd)
	{
		if (sentence->redirs[i].type == APPEND)
			w[1] = handle_redirection(sentence->redirs[i].path, APPEND, -1);
		else if (sentence->redirs[i].type == OUT_FILE)
			w[1] = handle_redirection(sentence->redirs[i].path, OUT_FILE, -1);
		else if (sentence->redirs[i].type == IN_FILE)
			w[0] = handle_redirection(sentence->redirs[i].path, IN_FILE, -1);
		else
			w[0] = handle_redirection(sentence->redirs[i].path, HERE_DOCS, \
			sentence->redirs[i].here_fd);
		i += 1;
	}
	if (sentence->inpipe)
	{
		if (!w[0])
			dup2(sentence->error, STDIN_FILENO);
	}
	if (sentence->outpipe && !w[1])
		dup2(pfd[STDOUT_FILENO], STDOUT_FILENO);
	pipe_closer(&pfd[STDIN_FILENO]);
	pipe_closer(&pfd[STDOUT_FILENO]);
	pipe_closer(&sentence->error);
}

/*
** keeps the last executed programs return value
*/
int	store_return_value(int ret_val, bool add)
{
	static int	ret;

	if (add)
		ret = ret_val;
	return (ret);
}
