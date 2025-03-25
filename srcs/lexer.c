/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:32:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/22 19:00:27 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mark_commands(t_char *cli, int i)
{
	if (i == 0 || cli[i].esc || cli[i - 1].esc || cli[i + 1].c == 0 || \
	cli[i + 1].esc)
		;
	else if (cli[i - 1].c == cli[i].c && !cli[i - 2].esc && cli[i - 2].c == \
	' ' && cli[i + 1].c == ' ' && (cli[i].c == '<' || cli[i].c == '>'))
	{
		cli[i].com = 1;
		cli[i - 1].com = 1;
	}
	else if (cli[i - 1].c == ' ' && cli[i].c == '>' && cli[i \
	+ 1].c == '>' && !cli[i + 2].esc && cli[i + 2].c == ' ')
	{
		cli[i].com = 1;
		cli[i + 1].com = 1;
	}
	else if (cli[i].c == '<' && cli[i + 1].c == '<' && cli[i + 2].c != 0 && \
	cli[i + 2].esc == 0 && cli[i + 2].c == ' ')
	{
		cli[i].com = 1;
		cli[i + 1].com = 1;
	}	
	else if (cli[i - 1].c != ' ' || cli[i + 1].c != ' ')
		;
	else if (cli[i].c == '|' || cli[i].c == '<' || cli[i].c == '>')
		cli[i].com = 1;
}

void	mark_env_var(t_char *newline, int start)
{
	int	end;

	end = start;
	newline[end].var = 1;
	end++;
	if (newline[end].c == 0 || newline[end].esc || (!ft_isalpha(newline[end].c)
			&& newline[end].c != '_'))
		return ;
	else
	{
		newline[end].var = 1;
		end++;
	}
	while (newline[end].ghost || (newline[end].c != 0 && !newline[end].esc
			&& (ft_isalnum(newline[end].c) || newline[end].c == '_')))
	{
		if (newline[end + 1].blok != 1)
			newline[end].var = 1;
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
		else if (newline[i].c == '$')
			mark_env_var(newline, i);
		i++;
	}
}

//di is passed as a 0 to reduce lines
void	expand_arguments(t_char *dst, t_char *src, t_data *data, int di)
{
	int			si;
	const char	*temp;

	si = 0;
	while (src[si].c != 0)
	{
		if (src[si].c == '$' && src[si].esc == 0 && src[si].var && \
		(ft_isalnum(src[si + 1].c) || src[si + 1].c == '_'))
		{
			temp = find_env(src + si, data);
			di = copy_env_to_tchar(dst, di, temp);
		}
		if (src[si].var == 0)
		{
			dst[di].ghost = src[si].ghost;
			dst[di].c = src[si].c;
			dst[di].esc = src[si].esc;
			dst[di].var = src[si].var;
			dst[di].com = src[si].com;
			dst[di].added = src[si].added;
			di++;
		}
		si++;
	}
	dst[di].c = 0;
}

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
