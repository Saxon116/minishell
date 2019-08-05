/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:13:16 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/05 17:49:41 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function checks if the environment variable passed
** into the name argument exists. The format given can be
** NAME or NAME=value.
**
** RETURN VALUE:
** If the variable exists, the function will return the index of
** the variable's position in the array. Otherwise -1 is returned
** since the returned value could be the 0th element of the array.
*/
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

/*
** DESCRIPTION:
** This function takes the name of an environment variable
** as an argument and returns that variable's value as an
** allocated string.
**
** RETURN VALUE:
** If the variable exists, the function will return the value
** of the environment variable. Otherwise, NULL is returned.
*/
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

/*
** DESCRIPTION:
** This function returns a string array containing the paths
** of the directories specified in the PATH environment variable.
**
** RETURN VALUE:
** If the PATH variable exists, the function will return the
** string array. Otherwise, NULL is returned.
*/
char **get_exec_paths(t_shell *shell)
{
	int index;

	index = check_env(shell, "PATH");
	if(index != -1)
		return (ft_strsplit(shell->environ[index] + 5, ":"));
	else
		return (NULL);
}
