/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:50:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 19:09:16 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int i is passed as 0
t_node	*create_node(t_char *line, size_t start, size_t size, int i)
{
	t_node	*node;
	t_char	*str;

	str = NULL;
	node = ft_xcalloc(sizeof(t_node), 1);
	if (line && line[start].c == 'G' && line[start].ghost)
		str = ft_xcalloc(sizeof(t_char), 1);
	else if (line)
	{
		str = ft_xcalloc(sizeof(t_char), size *2 + 20);
		while (line[start].c != 0 && (line[start].c != ' ' || line[start].esc))
		{
			if (!(line[start].c == 'G' && line[start].ghost))
			{
				str[i].c = line[start].c;
				str[i].esc = line[start].esc;
				str[i].var = line[start].var;
				str[i].com = line[start].com;
				i++;
			}
			start++;
		}
	}
	node->str = str;
	return (node);
}

void	create_list(t_data *data, t_char *line)
{
	size_t	i;
	size_t	strsize;

	i = 0;
	while (line[i].c != 0)
	{
		while (line[i].c != 0 && line[i].c == ' ' && line[i].esc == 0)
			i++;
		if (line[i].c == 0)
			break ;
		strsize = ft_wrdlen(line + i, data);
		if (ft_lstadd_back(&data->tokens, create_node(line, i, strsize, 0)))
			return ;
		while (line[i].c != 0)
		{
			if (line[i].c == ' ' && line[i].esc == 0)
				break ;
			i++;
		}
	}
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
