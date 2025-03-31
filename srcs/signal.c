/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:56:50 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/12 19:08:49 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig_nbr)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig_nbr;
}

void signal_handler_execution(int sig_nbr)
{
    if (sig_nbr == SIGINT)
        printf("\n");
    else if (sig_nbr == SIGQUIT)
        printf("Quit (core dumped)\n");
}

void	set_signals(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	unset_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	block_signals_in_parent(void)
{
	signal(SIGQUIT, &signal_handler_execution);
	signal(SIGINT, &signal_handler_execution);
}
