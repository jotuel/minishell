/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:05:42 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/08 18:17:38 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define RL_BEGIN "\001"
# define RL_END "\002"
# ifndef MAX_VARS
#  define MAX_VARS 100
# endif
# ifndef MAX_LENGTH
#  define MAX_LENGTH 667
# endif
# ifndef PATH_MAX
#  define PATH_MAX 5000
# endif
# define ENV_SIZE 400
# ifndef MAX_SENT_SIZE
#  define MAX_SENT_SIZE 2000
# endif
# ifndef MAX_SENTENCES
#  define MAX_SENTENCES 50
# endif
# ifndef EMOJI
#  define EMOJI "😎"
# endif
# ifndef USER
#  define USER "minishell"
# endif
#ifndef HOME
# define HOME ""
# endif
# ifndef PROMPT
#  define PROMPT ">"
# endif
# ifndef SHELL
#  define SHELL "minishell"
# endif
# ifndef DOC
#  define DOC "here document at line"
# endif
# ifndef WARN
#  define WARN "warning"
# endif
# ifndef DELIM
#  define DELIM "delimited by end-of-file"
# endif
#endif
