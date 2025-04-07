/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:50:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/07 12:13:26 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int i is passed as 0
t_node	*create_node(t_char *line, size_t sta, size_t size, int i)
{
	t_node	*node;
	t_char	*str;

	str = NULL;
	node = ft_xcalloc(sizeof(t_node), 1);
	if (line && line[sta].c == 'G' && line[sta].ghost)
		str = ft_xcalloc(sizeof(t_char), 1);
	else if (line)
	{
		str = ft_xcalloc(sizeof(t_char), size * 2 + 20);
		while (line[sta].c != 0 && (!ft_isspace(line[sta].c) || line[sta].esc))
		{
			if (!(line[sta].c == 'G' && line[sta].ghost))
			{
				str[i].c = line[sta].c;
				str[i].esc = line[sta].esc;
				str[i].var = line[sta].var;
				str[i].com = line[sta].com;
				i++;
			}
			sta++;
		}
	}
	node->str = str;
	return (node);
}

int	ft_isspace(unsigned char c)
{	
	if (c == '\n')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\v')
		return (1);
	else if (c == '\r')
		return (1);
	else if (c == ' ')
		return (1);
	else if (c == '\f')
		return (1);
	return (0);
}

void	create_list(t_data *data, t_char *line)
{
	size_t	i;
	size_t	strsize;

	i = 0;
	while (line[i].c != 0)
	{
		while (ft_isspace(line[i].c) && line[i].esc == 0)
			i++;
		if (line[i].c == 0)
			break ;
		strsize = ft_wrdlen(line + i, data);
		if (ft_lstadd_back(&data->tokens, create_node(line, i, strsize, 0)))
			return ;
		while (line[i].c != 0)
		{
			if (ft_isspace(line[i].c) && line[i].esc == 0)
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
