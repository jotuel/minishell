/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:59:49 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 19:57:26 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/rltypedefs.h>

static char	*ft_itoa_rec(unsigned int nbr, char *buffer)
{
	if (nbr >= 10)
		buffer = ft_itoa_rec(nbr / 10, buffer);
	*buffer = (nbr % 10) + '0';
	return (++buffer);
}

char	*ft_itoa(unsigned int nbr)
{
	static char	result[12];
	char		*buffer;

	buffer = result;
	buffer = ft_itoa_rec(nbr, buffer);
	*buffer = '\0';
	return (result);
}

static bool	check_write(int fd, char *txt, char *file_name)
{
	if (write(fd, txt, ft_strlen(txt)) < 0)
	{
		unlink(file_name);
		free(file_name);
		error_printf("system", "write failed");
		close(fd);
		free(txt);
		return (false);
	}
	return (true);
}


/*
** Creates a file, writes in it and unlinks it so that it is destroyed
** when the last fd closes. Memory address is used to create an unique
** suffix so 2 parallel minishells wont start with the same suffix
*/
int	open_temp_heredocs(t_node *node, int expand, char *eof, char *txt)
{
	int						fd;
	char					*file_name;
	static unsigned long	suffix = (unsigned long)&suffix;

	file_name = ft_strjoin("/tmp/here_docs_", ft_itoa(suffix++));
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0640);
	if (-1 == fd)
		return (free(file_name), fd);
	eof = cnvrt_to_char(node->str);
	rl_event_hook = heredoc_hook;
	txt = create_heredoc(eof, expand, NULL, NULL);
	rl_event_hook = NULL;
	free(eof);
	if (!check_write(fd, txt, file_name))
		return (-1);
	close(fd);
	fd = open(file_name, O_RDWR, 0640);
	unlink(file_name);
	free(file_name);
	free(txt);
	return (fd);
}
