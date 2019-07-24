/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:38:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/24 23:25:47 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **input, t_shell *shell)
{
	char *path;
	int i;
	int length;

	i = 0;
	length = 0;
	while(input[length])
		length++;
	if(length >= 3)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (0);
	}
	if(length == 2)
	{
		if(access(input[1], F_OK) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", input[1]);
			return (0);
		}
		if(access(input[1], X_OK) == -1)
		{
			ft_printf("minishell: cd: %s: Permission denied\n", input[1]);
			return (0);
		}
		chdir(input[1]);
	}
	else
	{
		path = ft_getenv(shell, "HOME");
		if(!path)
		{
			ft_printf("HOME environment variable not defined.\n");
			return (0);
		}
		while(path[i] != '=')
			i++;
		if(!path[i + 1])
		{
			ft_printf("HOME environment variable is empty.\n");
			return (0);
		}
		chdir(path + i + 1);
	}
	return (1);
}
