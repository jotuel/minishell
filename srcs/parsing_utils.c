/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:24 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 12:02:43 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Returns the lenght of custom char line
*/
size_t	ft_tcharlen(t_char *line)
{
	size_t	length;

	length = 0;
	while (line[length].c != '\0')
	{
		length++;
	}
	return (length);
}

/*
** Converts a custom line to regular line
** Extra space was reserved for escapes but seem redunant now
*/
char	*cnvrt_to_char(t_char *line)
{
	size_t	i;
	size_t	k;
	size_t	length;
	char	*result;

	i = 0;
	k = 0;
	length = ft_tcharlen(line) * 2;
	result = ft_xcalloc((ft_tcharlen(line) * 2) + 1, sizeof(char));
	while (i < length && line[k].c)
	{
		result[i] = line[k].c;
		i++;
		k++;
	}
	result[i] = '\0';
	return (result);
}

/*
**   when syntax error occurs frees stuff and returns NULL.
 */
t_sent	*syntax_error(t_node *node)
{
	char	*print;
	char	*tmp;
	char	*token;
	
	token = NULL;
	if (get_data()->tokens.first == node && node->type == PIPE)
		tmp = ft_strjoin("`", "|");

	else if (get_data()->tokens.last == node)
		tmp = ft_strjoin("`", "newline");
	else 
	{
		token = cnvrt_to_char(node->next->str);
		tmp = ft_strjoin("`", token);
	}
	free(token);
	token = NULL;
	deallocate(get_data());
	store_return_value(2, true);
	print = ft_strjoin(tmp, "\'");
	free (tmp);
	tmp = NULL;
	error_printf("syntax error near unexpected token", print);
	free(print);
	return (NULL);
}

size_t	ft_wrdlen(t_char *str, t_data *data)
{
	size_t	i;
	size_t	count_i;

	(void)data;
	i = 0;
	count_i = 0;
	if (str == NULL)
	{
		error_printf("system", "failure");
		return (-1);
	}
	while (str[i].c != 0 && (str[i].c != ' ' || str[i].esc == 1))
	{
		if (str[i].ghost == 0)
			count_i++;
		i++;
	}
	return (count_i);
}

// Tried to plug in but the prints failed due
int	file_has_error(char *path, enum e_token type)
{
	struct stat	file_stat;

	if (type == HERE_DOCS || type == HERE_QUOTE)
		return (0);
	if (stat(path, &file_stat) == -1)
	{
		if (errno == ENOENT)
			error_printf(path, "No such file or directory");
		else if (errno == EACCES)
			error_printf(path, "permission denied");
		else
			error_printf(path, "unknown stat error");
		return (1);
	}
	if (type == IN_FILE)
	{
		if (access(path, R_OK) == -1)
			return (error_printf(path, "permission denied"), 1);
	}
	else if (type == OUT_FILE || type == APPEND)
	{
		if (access(path, W_OK) == -1)
			return (error_printf(path, "permission denied"), 1);
	}
	return (0);
}
