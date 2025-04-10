/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:25:30 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/10 21:39:59 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**  opens a file as stdout where it ends. creating it only if needed.
*/
static void	handle_append(char *sent, int fd)
{
	fd = open(sent, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (-1 == fd)
		ft_exit(get_data(), sent, strerror(errno), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/*
**  opens a new empty file for writing as stdout.
*/
static void	handle_outfile(char *sent, int fd)
{
	fd = open(sent, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == fd)
		ft_exit(get_data(), sent, strerror(errno), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/*
** open a file as stdin to be read from.
*/
static void	handle_infile(char *sent, int fd)
{
	fd = open(sent, O_RDONLY);
	if (-1 == fd)
		ft_exit(get_data(), sent, strerror(errno), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/*
** takes the heredoc tmp file and makes that stdin.
*/
static void	handle_heredoc(int fd)
{
	t_data	*data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data = get_data();
	dup2(fd, STDIN_FILENO);
	while (data->page[i])
	{
		while (j < 20)
			if (data->page[i]->redirs[j++].here_fd > 2)
				close(data->page[i]->redirs[j - 1].here_fd);
		j = 0;
		i += 1;
	}
	close(fd);
}

/*
** check enum type.
*/
bool	handle_redirection(char *sentence, enum e_token type, int fd)
{
	if (type == APPEND)
		handle_append(sentence, fd);
	else if (type == OUT_FILE)
		handle_outfile(sentence, fd);
	else if (type == IN_FILE)
		handle_infile(sentence, fd);
	else
		handle_heredoc(fd);
	return (true);
}
