/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:32:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/03 11:14:36 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mark_commands(t_char *cl, int i)
{
	if (!i || cl[i].esc || cl[i - 1].esc || cl[i + 1].c == 0 || cl[i + 1].esc)
		;
	else if (cl[i - 1].c == cl[i].c && !cl[i - 2].esc && cl[i - 2].c == ' '
		&& cl[i + 1].c == ' ' && (cl[i].c == '<' || cl[i].c == '>'))
	{
		cl[i].com = 1;
		cl[i - 1].com = 1;
	}
	else if (cl[i - 1].c == ' ' && cl[i].c == '>' && cl[i + 1].c == '>'
		&& !cl[i + 2].esc && cl[i + 2].c == ' ')
	{
		cl[i].com = 1;
		cl[i + 1].com = 1;
	}
	else if (cl[i].c == '<' && cl[i + 1].c == '<' && cl[i + 2].c != 0
		&& cl[i + 2].esc == 0 && cl[i + 2].c == ' ')
	{
		cl[i].com = 1;
		cl[i + 1].com = 1;
	}
	else if (cl[i - 1].c != ' ' || cl[i + 1].c != ' ')
		;
	else if (cl[i].c == '|' || cl[i].c == '<' || cl[i].c == '>')
		cl[i].com = 1;
}

void	mark_env_var(t_char *nl, int end)
{
	nl[end].var = 1;
	end++;
	if (nl[end].c == 0 || nl[end].esc || (!ft_isalpha(nl[end].c)
			&& nl[end].c != '_' && nl[end].c != '?'))
		return ;
	else
	{
		nl[end].var = 1;
		if (nl[end].c == '?')
			return ;
		end++;
	}
	while (nl[end].ghost || (nl[end].c != 0 && !nl[end].esc
			&& (ft_isalnum(nl[end].c) || nl[end].c == '_')))
	{
		if (nl[end + 1].blok != 1)
		{
			nl[end].var = 1;
		}
		else
			return ;
		end++;
	}
}

void	mark_arguments(t_char *newline)
{
	int	i;

	i = 0;
	while (newline[i].c != 0)
	{
		if (newline[i].esc)
			;
		else if (newline[i].c == '$' && \
		(question_or_underscore(newline[i + 1].c) \
		|| ft_isalnum(newline[i + 1].c)))
		{
			mark_env_var(newline, i);
		}
		i++;
	}
}

// di is passed as a 0 to reduce lines
void	expand_arguments(t_char *dst, t_char *c, t_data *data, int di)
{
	int			i;
	const char	*temp;

	i = 0;
	while (c[i].c != 0)
	{
		if (c[i].c == '$' && c[i].esc == 0 && c[i].var
			&& (ft_isalnum(c[i + 1].c) || question_or_underscore(c[i + 1].c)))
		{
			temp = find_env(c + i, data);
			di = copy_env_to_tchar(dst, di, temp);
		}
		if (c[i].var == 0)
		{
			dst[di].ghost = c[i].ghost;
			dst[di].c = c[i].c;
			dst[di].esc = c[i].esc;
			dst[di].var = c[i].var;
			dst[di].com = c[i].com;
			dst[di].added = c[i].added;
			di++;
		}
		i++;
	}
	dst[di].c = 0;
}

bool	check_for_all_spaces(t_char *line);

// dynamic memory is problematic due to unknown sizes,
//	last few characters are missing sometimes
t_char	*lexify(char *line, t_data *data)
{
	t_char			*newline;
	static t_char	expanded[1000];
	int				i;

	newline = ft_xcalloc(ft_strlen(line) * 3 + 10, sizeof(t_char));
	remove_quotes(newline, line, 0, 0);
	i = 0;
	while (newline[i].c != 0)
		mark_commands(newline, i++);
	mark_arguments(newline);
	expand_arguments(expanded, newline, data, 0);
	create_list(data, expanded);
	return (newline);
}
