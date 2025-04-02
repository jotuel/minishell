/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:56:50 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/01 12:45:15 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Signal handler for SIGINT and SIGQUIT signals.
 */
void	signal_handler(int sig_nbr)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig_nbr;
}

/*
 * Signal handler for SIGINT and SIGQUIT signals during execution.
 */
void	signal_handler_execution(int sig_nbr)
{
	if (sig_nbr == SIGINT)
		printf("\n");
	else if (sig_nbr == SIGQUIT)
		printf("Quit (core dumped)\n");
}

/*
 * Set signal handlers for SIGINT and SIGQUIT signals.
 */
void	set_signals(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Unset signal handlers for SIGINT and SIGQUIT signals.
 */
void	unset_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

/*
 * Block signals in parent process.
 */
void	block_signals_in_parent(void)
{
	signal(SIGQUIT, &signal_handler_execution);
	signal(SIGINT, &signal_handler_execution);
}
