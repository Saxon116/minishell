/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/18 17:39:07 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtin(char **input, char **environ)
{
	if(ft_strcmp(input[0], "cd") == 0)
		return (cd(input, environ));
	if(ft_strcmp(input[0], "exit") == 0)
		exit(0);
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
