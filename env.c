/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:13:16 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/24 23:25:05 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_env(t_shell *shell, char *name)
{
  int i;
	int found;

	i = 0;
	found = 0;
	while(shell->environ[i])
	{
		if(ft_strstr(shell->environ[i], name))
		{
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return (i);
	else
		return (-1);
}

char *ft_getenv(t_shell *shell, char *name)
{
	if(check_env(shell, name) != -1)
		return (ft_strdup(shell->environ[check_env(shell, name)]));
	else
		return (NULL);
}

char **get_exec_paths(t_shell *shell)
{
	int i;
	int found;

	i = 0;
	found = 0;
	while(shell->environ[i])
	{
		if(ft_strnstr(shell->environ[i], "PATH", 5))
		{
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return (ft_strsplit(shell->environ[i] + 5, ":"));
	else
		return (NULL);
}
