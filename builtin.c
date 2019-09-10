/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/09/10 15:39:12 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function implements the most basic echo command by printing
** the arguments that are sent into it.
*/

void	echo(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (i != 1)
			ft_printf(" ");
		ft_printf(input[i]);
		i++;
	}
	ft_printf("\n");
}

/*
** DESCRIPTION:
** This function checks if the new environment variable is in the
** correct "VARNAME=value" format before calling the add_env_var
** function to save the new value into the environ array.
**
** RETURN VALUE:
** On success, 1 is returned. On error, 0 is returned.
**
** EXTERNAL FUNCTIONS:
** add_env_var is located in edit_env.c
*/

int		ft_setenv(t_shell *shell)
{
	int		length;
	char	**new_var;

	length = 0;
	while (shell->input[length])
		length++;
	if (length != 2)
	{
		ft_printf("usage: setenv VARNAME=value\n");
		return (0);
	}
	new_var = ft_strsplit(shell->input[1], "=");
	length = 0;
	while (new_var[length])
		length++;
	free_string_array(new_var);
	if (length != 2)
	{
		ft_printf("Cannot have an empty field.\
		\nusage: setenv VARNAME=value\n");
		return (0);
	}
	add_env_var(shell, shell->input[1]);
	return (1);
}

/*
** DESCRIPTION:
** This function checks if the environment variable to be deleted
** is already set before calling the del_env_var function to
** remove the variable from the environ array.
**
** RETURN VALUE:
** On success, 1 is returned. On error, 0 is returned.
**
** EXTERNAL FUNCTIONS:
** cd function is located in cd.c
*/

int		ft_unsetenv(t_shell *shell)
{
	int length;
	int index;

	length = 0;
	while (shell->input[length])
		length++;
	if (length != 2)
	{
		ft_printf("usage: unsetenv VARNAME\n");
		return (0);
	}
	index = check_env(shell, shell->input[1]);
	if (index == -1)
	{
		ft_printf("%s is not set.\n", shell->input[1]);
		return (0);
	}
	del_env_var(shell, index);
	return (1);
}

/*
** DESCRIPTION:
** This function calls the appropriate builtin command function.
**
** RETURN VALUE:
** It returns 1 if the builtin ran correctly, or 0 if it failed.
**
** EXTERNAL FUNCTIONS:
** cd function is located in cd.c
*/

int		run_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->input[0], "cd") == 0)
		return (cd(shell));
	if (ft_strcmp(shell->input[0], "echo") == 0)
		echo(shell->input);
	if (ft_strcmp(shell->input[0], "exit") == 0)
	{
		free_shell_vars(shell);
		exit(0);
	}
	if (ft_strcmp(shell->input[0], "env") == 0)
		print_string_array(shell->environ);
	if (ft_strcmp(shell->input[0], "setenv") == 0)
		ft_setenv(shell);
	if (ft_strcmp(shell->input[0], "unsetenv") == 0)
		ft_unsetenv(shell);
	return (0);
}

/*
** DESCRIPTION:
** This function checks if the program to be run is one of
** minishell's builtins.
**
** RETURN VALUE:
** It returns 1 if the command to be run is a builtin,
** or 0 if it is not.
*/

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "setenv") == 0)
		return (1);
	if (ft_strcmp(command, "unsetenv") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	return (0);
}
