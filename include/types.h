/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:20:09 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/13 15:57:54 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "macro.h"

typedef struct s_char
{
	char			c;
	bool			esc;
	bool			com;
	bool			var;
	bool			blok;
	bool			ghost;
	bool			added;
	bool			multi;
}					t_char;

typedef enum e_token
{
	DELIMIT,
	ARG,
	OUT_FILE,
	IN_FILE,
	PIPE,
	REDIRECT,
	HERE_DOCS,
	APPEND,
	HERE_QUOTE
}					t_token;

typedef struct s_ldiv
{
	long int		quot;
	long int		rem;
}					t_ldiv;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	t_char			*str;
	t_token			type;
}					t_node;

typedef struct s_list
{
	t_node			*first;
	t_node			*last;
}					t_list;

typedef struct s_dir
{
	char			*path;
	t_token			type;
	int				here_fd;

}					t_dir;

typedef struct s_sent
{
	char			*array[MAX_SENT_SIZE];
	bool			inpipe;
	t_dir			redirs[20];
	bool			outpipe;
	int				pipe_end;
	int				heredocs;
	int				argc;
}					t_sent;

typedef struct s_data
{
	char			**path;
	char			env[ENV_SIZE + 1][MAX_LENGTH + 1];
	int				env_count;
	t_list			tokens;
	t_sent			*page[MAX_SENT_SIZE];
	int				herecount;
	char			cwd[200];
	t_char			*newline;
	int				error;
}					t_data;

typedef struct s_point
{
	t_node			*node;
	int				start;
	int				end;
}					t_point;
#endif
