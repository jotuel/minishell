/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:40 by jrimpila          #+#    #+#             */
/*   Updated: 2025/04/01 17:00:12 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Gets the variable name value and location of the free slot as input
//	 and writes the value there
int	set_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar,
		char *value, int free_slot)
{
	int	i;
	int	k;

	i = 0;
	while (envvar[i] && i < MAX_LENGTH)
	{
		env[free_slot][i] = envvar[i];
		i++;
	}
	if (envvar[i])
		return (error_printf("export", "Env max exceeded"), 1);
	if (value && i < MAX_LENGTH)
		env[free_slot][i++] = '=';
	k = 0;
	while (value && value[k] && i < MAX_LENGTH)
	{
		env[free_slot][i] = value[k];
		i++;
		k++;
	}
	if (value[k])
		return (error_printf("export", "Env max exceeded"), 1);
	return (0);
}

// First it unsets the variable, then it adds it with a new value
int	add_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar,
		char *value)
{
	int	i;

	if (envvar == NULL || value == NULL || env == NULL)
		return (1);
	unset_one(envvar);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i][0] == '\0')
			return (set_envvar(env, envvar, value, i));
		i++;
	}
	error_printf("export", "env variables full");
	return (231);
}

//Checks that export identifiers are valid
int	errorcheck_expand(char *var)
{
	int	i;

	i = 0;
	if (!var || (var[i] != '_' && ft_isalpha(var[i]) == 0))
	{
		printf("minishell: export: `%s': not a valid identifier\n", var);
		return (1);
	}
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	if (var[i] != 0 && var[i] != '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", var);
		return (1);
	}
	return (0);
}

void	process_new_envvarr(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *var)
{
	char	name[MAX_LENGTH + 1];
	char	value[MAX_LENGTH + 1];
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (k < MAX_LENGTH + 1 && var[i] != '=' && var[i] != '\0')
	{
		name[k] = var[i];
		i++;
		k++;
	}
	name[k] = '\0';
	if (var[i] == '=')
		i++;
	k = 0;
	while (k < MAX_LENGTH + 1 && var[i] != '\0')
	{
		value[k] = var[i];
		k++;
		i++;
	}
	value[k] = '\0';
	add_envvar(env, name, value);
}

//BASH goes through the arguments and even if 
//there is error in one it applies the rest
// if any one of them fails the return value is 1
int	bi_export(int argc, char *argv[], t_sent *sent, int fd)
{
	int	i;
	int	retval;

	retval = 0;
	if (argc == 1)
		return (print_alphabetically(get_data()->env, fd));
	i = 1;
	while (i < argc)
	{
		retval = errorcheck_expand(argv[i]);
		if (argv[i] && retval == 0)
		{
			if (sent->inpipe == 0 && sent->outpipe == 0)
				process_new_envvarr(get_data()->env, argv[i]);
		}
		else
			retval = 1;
		i++;
	}
	return (retval);
}
