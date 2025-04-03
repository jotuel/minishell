/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:25:30 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/25 15:59:17 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

/*
**  opens a file as stdout where it ends. creating it only if needed.
*/
static void	handle_append(char *sent, int fd)
{
	fd = open(sent, O_WRONLY | O_CREAT, 0644);
	if (-1 == fd)
		ft_exit(get_data(), sent, strerror(errno), errno);
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
		ft_exit(get_data(), sent, strerror(errno), errno);
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
		ft_exit(get_data(), sent, strerror(errno), errno);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/*
** takes the heredoc tmp file and makes that stdin.
*/
static void	handle_heredoc(int fd)
{
	dup2(fd, STDIN_FILENO);
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
