/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:40:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/15 19:41:26 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtin(char **input)
{
	if(ft_strcmp(input[0], "cd") == 0)
		return (cd(input));
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

int cd(char **input)
{
	if(input[1])
		chdir(input[1]);
	return (1);
}
