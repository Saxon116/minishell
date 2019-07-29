/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:43:24 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/29 18:33:08 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **replace_tilde(t_shell *shell, char **input)
{
	int i;
	int length;
	char **new_array;

	length = 0;
	while(input[length])
		length++;
	if(length < 2)
		return (NULL);
	i = 1;
	if(check_env(shell, "HOME") == -1)
	{
		ft_printf("HOME not set.\n");
		return (NULL);
	}
	new_array = string_arr_cpy(input);
	while(input[i])
	{
		free(new_array[i]);
		new_array[i] = replace_substring(input[i], "~", shell->home);
		i++;
	}
	return (new_array);
}

int is_dir(char *path)
{
	char temp_buf[1024];
	char buf[1024];
	struct stat		pstat;
	int len;

	bzero(buf, 1024);
	lstat(path, &pstat);
	if (lstat(path, &pstat) == -1)
		return (0);
	if(!S_ISLNK(pstat.st_mode))
		return (S_ISDIR(pstat.st_mode));
	else
	{
		len = readlink(path, temp_buf, 1023);
		if (len != -1)
			temp_buf[len] = '\0';
		if(temp_buf[0] != '/')
			buf[0] = '/';
		ft_strcat(buf, temp_buf);
		if (lstat(buf, &pstat) == -1)
			return (0);
		return (S_ISDIR(pstat.st_mode));
	}
}

void parse_command(char **input, t_shell *shell)
{
	char *command_path;
	char **new_input;
	char **exec_paths;
	int has_tilde;

	has_tilde = 1;
	new_input = replace_tilde(shell, input);
	if(!new_input)
	{
		new_input = input;
		has_tilde = 0;
	}
	if(is_builtin(new_input[0]))
		run_builtin(new_input, shell);
	else
	{
		exec_paths = get_exec_paths(shell);
		command_path = find_command(new_input[0], exec_paths);
		if(!command_path)
			ft_printf("minishell: %s: command not found\n", new_input[0]);
		else
			if(is_dir(command_path))
				ft_printf("minishell: %s: Is a directory\n", command_path);
			else
				run(command_path, new_input, shell->environ);
		if(exec_paths)
			free_string_array(exec_paths);
		free(command_path);
	}
	if(has_tilde)
		free_string_array(new_input);
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
		if (ft_strcmp(pdirent->d_name, name) == 0
		&& pdirent->d_type != DT_DIR)
		{
			ft_strcat(path, pdirent->d_name);
			if (lstat(path, &pstat) == -1)
			{
				closedir(pdir);
				return (0);
			}
			if(access(path, X_OK) != -1)
			{
				closedir(pdir);
				return (ft_strdup(path));
			}
			ft_bzero(path + ft_strlen(exec_path) + 1, ft_strlen(pdirent->d_name));
		}
	}
	closedir(pdir);
	return (NULL);
}

char *find_command(char *name, char **exec_paths)
{
	int i;
	char *command_path;

	i = 0;
	if(ft_strlen(name) >= 3 && contains(name, '/') == 1)
		if(name[0] == '.' && name[1] == '/')
			if(access(name, F_OK) != -1 && access(name, X_OK) != -1)
				return (ft_strdup(name));
	if(ft_strlen(name) >= 3 && contains(name, '/'))
		if(name[0] == '/')
			if(access(name, F_OK) != -1 && access(name, X_OK) != -1)
				return (ft_strdup(name));
	if(!contains(name, '/') && exec_paths)
		while(exec_paths[i])
		{
			command_path = search_command(name, exec_paths[i]);
			if(command_path)
				return (command_path);
			i++;
		}
	return (NULL);
}
