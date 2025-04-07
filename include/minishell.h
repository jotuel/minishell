/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/07 17:45:36 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h" // our own library
# include "color.h" // different control codes
# include <readline/history.h> // add_history
# include <readline/readline.h> // readline
# include <linux/binfmts.h> // ARG_MAX_STRLEN
# include <errno.h> // error number
# include <fcntl.h> // open
# include <sys/user.h> // PAGE_SIZE
# include <sys/stat.h> // fstat
# include <sys/wait.h> // WEXITSTATUS

/*
** BUILT' INS
*/
int				cwd(t_data *data);
int				run_builtin(int argc, char *argv[], t_sent *sent, bool update);
int				is_builtin(char *cmd);
int				bi_pwd(int fd);
int				bi_cd(int argc, char *argv[], t_sent *sent);
void			bi_env(t_data *data, int fd);
int				bi_echo(int argc, char *argv[], int fd);
int				bi_unset(int argc, char *argv[], t_sent *sent);
int				bi_export(int argc, char *argv[], t_sent *sent, int fd);
int				bi_exit(int argc, char *argv[], t_sent *sentence);
const char		*ft_get_env(const char *target);
int				add_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar,
					char *value);
const char		*find_env_value(char *source, t_data *data);
int				builtin_cd(char *path);

/*
** BUILT' IN UTILS
*/
int				print_alphabetically(char env[ENV_SIZE + 1][MAX_LENGTH + 1],
					int fd);
int				unset_one(char *env_val);
int				file_closer(int fd);
int				infile_checker(char *name);
int				file_has_error(char *path, enum e_token type);

/*
** ENVVAR UTILS
*/
void			expand_envvar(char *unexp, char *exp, int *i, int *k);
void			update_env(int value, char *name, bool update);
int				question_or_underscore(char c);

/*
** EXECUTION
*/
void			util_parse_args(t_data *data, int i);
int				execute(t_sent *sentence, int pfd[2], pid_t my_child,
					t_data *data);
int				store_return_value(int ret_val, bool add);
void			pipe_closer(int *fd);

/*
** EXIT & ERROR PRINTING
*/
void			ft_exit(t_data *data, char *cmd, char *message, int exit_code);
void			error_printf(char *cmd, char *message);
void			test(void);
void			deallocate(t_data *data);
int				ft_atoi_spec(const char *nptr, int sign, long ret);
t_sent			*syntax_error(t_node *node);

/*
** UTILITIES
*/
typedef void	(*t_node_func)(t_list *list, t_node *node);
void			*ft_xcalloc(size_t nmemb, size_t size);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_wrdlen(t_char *str, t_data *data);
const char		*find_env(t_char *source, t_data *data);
void			create_list(t_data *data, t_char *line);
void			iterate_list(t_list *list, t_node_func func);
t_data			*get_data(void);
void			debug_print(t_char *array, t_data *data);
void			print_node(t_list *list, t_node *node);
size_t			ft_tcharlen(t_char *line);
t_node			*destroy_node(t_list *list, t_node *node);
int				copy_env_to_tchar(t_char *dst, int i, const char *env);
char			*cnvrt_to_char(t_char *line);
void			destroy_old_page(int i, int j, int k, t_data *data);
char			*ft_itoa(unsigned int nbr);
int				all_isspace(char *nptr);
char			**get_own_env(void);

/*
** LEXING & PARSING
*/
t_char			*lexify(char *line, t_data *data);
t_sent			**create_page(t_list *stack);
void			print_sentence(t_sent *sentence);
char			*create_heredoc(char *terminator, int expand, char *result,
					char *tmp);
bool			is_file(t_token type);
char			*test_outfile(t_char *raw_path);
char			*test_append(t_char *raw_path);
int				prompt_input(char *line, int pfd[2], t_data *data, int input);
void			add_redirection(t_node *node, t_sent *sentence, int i);
t_sent			*conv_linked_to_sentence(int i, int k, t_node *node, \
				t_sent *sent);
int				check_emp_arg(char *src, int i, t_char *dst, int *k);
void			remove_quotes(t_char *dst, char *src, int i, int k);
int				open_temp_heredocs(t_node *node, int expand, char *eof,
					char *txt);
void			mark_commands(t_char *com_line, int i);

/*
** LEXING & PARSING UTILS
*/

int				handle_rest(char *src, t_char *dst, int i, int *k);
int				handle_d_quotes(char *src, t_char *dst, int *k, int *exp);
int				handle_s_quotes(char *src, t_char *dst, int i, int *k);
void			get_more_input(void);

/*
** SIGNALS
*/
void			block_signals_in_parent(void);
void			set_signals(void);
void			signal_handler(int sig_nbr);
void			void_signal(int sig_nbr);
void			unset_signals(void);

#endif
