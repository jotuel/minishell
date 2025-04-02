/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:24 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/02 16:02:55 by jrimpila         ###   ########.fr       */
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
t_sent	*syntax_error(char *token, t_sent **sentence)
{
	deallocate(get_data());
	free(*sentence);
	(*sentence) = NULL;
	error_printf("syntax error near unexpected token", token);
	return (NULL);
}
