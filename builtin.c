/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/28 21:26:49 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function implements the most basic echo command by printing
** the arguments that are sent into it.
*/
void echo(char **input)
{
	int i;

	i = 1;
	while(input[i])
	{
		if(i != 1)
			ft_printf(" ");
		ft_printf(input[i]);
		i++;
	}
	ft_printf("\n");
}

/*
** DESCRIPTION:
** This function checks if the new environment variable is in the
** correct "VAR_NAME=value" format before calling the add_env_var
** function to save the new value into the environ array.
**
** RETURN VALUE:
** On success, 1 is returned. On error, 0 is returned.
**
** EXTERNAL FUNCTIONS:
** add_env_var is located in edit_env.c
*/
int ft_setenv(t_shell *shell, char **input)
{
	int length;
	char **new_var;

	length = 0;
	while(input[length])
		length++;
	if(length != 2)
	{
		ft_printf("usage: setenv VARNAME=value\n");
		return (0);
	}
	new_var = ft_strsplit(input[1], "=");
	length = 0;
	while(new_var[length])
		length++;
	if(length != 2)
	{
		ft_printf("Cannot have an empty field.\
		\nusage: setenv VARNAME=value\n");
		return (0);
	}
	free(new_var);
	add_env_var(shell, input[1]);
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
int ft_unsetenv(t_shell *shell, char **input)
{
	int length;
	int index;

	length = 0;
	while(input[length])
		length++;
	if(length != 2)
	{
		ft_printf("usage: unsetenv VARNAME\n");
		return (0);
	}
	index = check_env(shell, input[1]);
	if(index == -1)
	{
		ft_printf("%s is not set.\n", input[1]);
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
int run_builtin(char **input, t_shell *shell)
{
	if(ft_strcmp(input[0], "cd") == 0)
		return (cd(input, shell));
	if(ft_strcmp(input[0], "echo") == 0)
		echo(input);
	if(ft_strcmp(input[0], "exit") == 0)
		exit(0);
	if(ft_strcmp(input[0], "env") == 0)
		print_char_array(shell->environ);
	if(ft_strcmp(input[0], "setenv") == 0)
		ft_setenv(shell, input);
	if(ft_strcmp(input[0], "unsetenv") == 0)
		ft_unsetenv(shell, input);
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
int is_builtin(char *command)
{
	char *builtins[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"
, 0};
	int i;

	i = 0;
	while(builtins[i])
	{
		if(ft_strcmp(command, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
