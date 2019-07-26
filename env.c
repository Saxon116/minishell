/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:13:16 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/26 18:16:32 by nkellum          ###   ########.fr       */
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
		if(ft_strnstr(shell->environ[i], name, ft_strlen(name)))
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
  int i;
  char *path;

  i = 0;
	if(check_env(shell, name) != -1)
  {
    path = shell->environ[check_env(shell, name)];
    while(path[i] != '=')
			i++;
		return (ft_strdup(path + i + 1));
  }
	else
		return (NULL);
}

char **get_exec_paths(t_shell *shell)
{
	int index;

	index = check_env(shell, "PATH");
	if(index != -1)
		return (ft_strsplit(shell->environ[index] + 5, ":"));
	else
		return (NULL);
}
