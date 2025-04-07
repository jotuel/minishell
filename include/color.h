/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:02:56 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/06 14:28:25 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "macro.h"
#ifndef COLOR_H
# define COLOR_H
# define RED "\x1b[31m"
# define GREEN RL_BEGIN "\x1b[32m" RL_END
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BRIGHT_BLACK "\x1b[90m"
# define BRIGHT_RED "\x1b[91m"
# define BRIGHT_GREEN "\x1b[92m"
# define BRIGHT_YELLOW RL_BEGIN "\x1b[93m" RL_END
# define BRIGHT_BLUE "\x1b[94m"
# define BRIGHT_MAGENTA "\x1b[95m"
# define BRIGHT_CYAN "\x1b[96m"
# define BRIGHT_WHITE "\x1b[97m"
# define RESET RL_BEGIN "\x1b[0m" RL_END
#endif
