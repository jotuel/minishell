/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/05 09:57:03 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	amount_of_spaces(char *nptr);

static void	error_print_spec(const char *cmd, const char *message1,
		const char *message2)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s: %s\n", cmd, message1, message2);
}

int	overflow_check(long ret, int sign, int addition, const char *nptr)
{
	if (ret == 922337203685477580 && addition > 7)
	{
		error_print_spec("exit", nptr, "numeric argument required");
		return (2);
	}
	if (ret >= 922337203685477581)
	{
		error_print_spec("exit", nptr, "numeric argument required");
		return (2);
	}
	if (ret == 922337203685477580 && addition > 8 && sign == -1)
	{
		error_print_spec("exit", nptr, "numeric argument required");
		return (2);
	}
	return (0);
}

// Meant to handle the inbuilt exit the same way as bash.
// int sign should be passed as 1
int	ft_atoi_spec(const char *nptr, int sign, long ret)
{
	int	i;

	ret = 0;
	i = amount_of_spaces((char *)nptr);
	if (nptr[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		if (overflow_check(ret, sign, (nptr[i] - '0'), nptr))
			return (2);
		ret *= 10;
		ret += nptr[i] - '0';
		i++;
	}
	if (nptr[i] != 0)
	{
		error_print_spec("exit", nptr, "numeric argument required");
		return (2);
	}
	return ((char)ret * sign);
}

static int	amount_of_spaces(char *nptr)
{
	size_t	ret;

	ret = 0;
	while (ft_isspace(nptr[ret]))
		ret++;
	return (ret);
}

int	all_isspace(char *nptr)
{
	size_t	ret;

	ret = 0;
	while (nptr[ret])
		if (!ft_isspace(nptr[ret++]))
			return (0);
	return ((ret));
}
