/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:00:18 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/08 17:00:18 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int  rl_hook(void)
{
    if(g_sig == SIGINT)
    {
        g_sig = 0;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        return (0);
    }
    return (0);
}

int  prompt_hook(void)
{
    return (0);
}

int  heredoc_hook(void)
{
    if(g_sig == SIGINT)
    {
        rl_pending_input = 4;
        rl_done = 1;
        return (0);
    }
    return (0);
}
