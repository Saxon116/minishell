/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:13:16 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/18 17:33:52 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *name, char **environ)
{
  int i;
	int found;

	i = 0;
	found = 0;
	while(environ[i])
	{
		if(ft_strstr(environ[i], name))
		{
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return (ft_strdup(environ[i]));
	else
		return (NULL);
}

char **get_exec_paths(char **environ)
{
	int i;
	int found;

	i = 0;
	found = 0;
	while(environ[i])
	{
		if(ft_strnstr(environ[i], "PATH", 5))
		{
			found = 1;
			break;
		}
		i++;
	}
	if(found)
		return (ft_strsplit(environ[i] + 5, ':'));
	else
		return (NULL);
}
