/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:13:16 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/25 14:35:25 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_env(t_shell *shell, char *name)
{
	int i;
	int found;
	int length;

	i = 0;
	length = 0;
	found = 0;
	while(shell->environ[i])
	{
		length = ft_strchr(shell->environ[i], '=') - shell->environ[i];
		if(ft_strnstr(shell->environ[i], name, length))
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
	int index;

	index = check_env(shell, "PATH");
	if(index != -1)
		return (ft_strsplit(shell->environ[index] + 5, ":"));
	else
		return (NULL);
}
