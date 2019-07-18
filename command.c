/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:43:24 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/18 17:23:32 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_command(char **input, char **environ)
{
	char *command_path;

	if(is_builtin(input[0]))
		run_builtin(input, environ);
	else
	{
		command_path = find_command(input[0], get_exec_paths(environ));
		if(!command_path)
			ft_printf("minishell: %s: command not found\n", input[0]);
		else
			run(command_path, input, environ);
	}
}

char *search_command(char *name, char *exec_path)
{
	DIR *pdir;
	struct dirent *pdirent;
	struct stat		pstat;
	char path[1024];

	ft_strcpy(path, exec_path);
	ft_strcat(path, "/");
	pdir = opendir(exec_path);
	if(!pdir)
	return (NULL);
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (ft_strcmp(pdirent->d_name, name) == 0 && pdirent->d_type != DT_DIR)
		{
			ft_strcat(path, pdirent->d_name);
			if (lstat(path, &pstat) == -1)
				return (0);
			if((pstat.st_mode & S_IXUSR) || (pstat.st_mode & S_IXGRP)
			|| (pstat.st_mode & S_IXOTH))
				return (ft_strdup(path));
			ft_bzero(path + ft_strlen(exec_path) + 1, ft_strlen(pdirent->d_name));
		}
	}
	return (NULL);
}

char *find_command(char *name, char **exec_paths)
{
	int i;
	char *command_path;

	i = 0;
	while(exec_paths[i])
	{
		command_path = search_command(name, exec_paths[i]);
		if(command_path)
		return (command_path);
		i++;
	}
	return (NULL);
}
