/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/25 14:10:13 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(char **input)
{
	int i;

	i = 1;
	while(input[i])
	{
		ft_printf(input[i]);
		i++;
	}
	ft_printf("\n");
	return (1);
}

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
