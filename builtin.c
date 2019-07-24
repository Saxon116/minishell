/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/23 16:42:04 by nkellum          ###   ########.fr       */
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

int run_builtin(char **input, char **environ)
{
	if(ft_strcmp(input[0], "cd") == 0)
		return (cd(input, environ));
	if(ft_strcmp(input[0], "echo") == 0)
		echo(input);
	if(ft_strcmp(input[0], "exit") == 0)
		exit(0);
	if(ft_strcmp(input[0], "env") == 0)
		print_char_array(environ);
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
