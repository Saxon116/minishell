/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:43:24 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 12:34:47 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function checks if the path specified is a directory.
** If it is a symbolic link, it will check if the symbolic link
** points to a directory.
**
** RETURN VALUE:
** If the path specified is a directory, 1 is returned. Otherwise,
** 0 is returned.
*/

int		is_dir(char *path)
{
	char		temp_buf[1024];
	char		buf[1024];
	struct stat	pstat;
	int			len;

	ft_bzero(buf, 1024);
	lstat(path, &pstat);
	if (lstat(path, &pstat) == -1)
		return (0);
	if (!S_ISLNK(pstat.st_mode))
		return (S_ISDIR(pstat.st_mode));
	else
	{
		len = readlink(path, temp_buf, 1023);
		if (len != -1)
			temp_buf[len] = '\0';
		if (temp_buf[0] != '/')
			buf[0] = '/';
		ft_strcat(buf, temp_buf);
		if (lstat(buf, &pstat) == -1)
			return (0);
		return (S_ISDIR(pstat.st_mode));
	}
}

/*
** DESCRIPTION:
** This function replaces any tildes with the HOME value,
** or any environment variable name with a dollar in front
** with its value. The changes are stored in the input
** variable of the shell structure.
**
** EXTERNAL FUNCTIONS:
** replace_tilde is located in replace.c
** replace_dollar_env is located in replace.c
*/

void	replace_input(t_shell *shell)
{
	char	**new_input;
	char	**temp;

	temp = replace_tilde(shell, shell->input);
	if (!temp)
		new_input = replace_dollar_env(shell, shell->input);
	else
		new_input = replace_dollar_env(shell, temp);
	if (new_input)
	{
		free_string_array(shell->input);
		shell->input = new_input;
		free_string_array(temp);
		temp = NULL;
	}
	else
	{
		if (temp)
		{
			free_string_array(shell->input);
			shell->input = temp;
		}
	}
}

/*
** DESCRIPTION:
** This function parses the command given to minishell and runs
** the appropriate command if it is available.
**
** EXTERNAL FUNCTIONS:
** is_builtin is located in builtin.c
** run_builtin is located in builtin.c
** run is located in shell.c
** get_exec_paths is located in env.c
*/

void	parse_command(t_shell *shell)
{
	char	*command_path;
	char	**exec_paths;

	replace_input(shell);
	if (is_builtin(shell->input[0]))
		run_builtin(shell);
	else
	{
		exec_paths = get_exec_paths(shell);
		command_path = find_command(shell->input[0], exec_paths);
		if (!command_path)
			ft_printf("minishell: %s: command not found\n", shell->input[0]);
		else
		{
			if (is_dir(command_path))
				ft_printf("minishell: %s: Is a directory\n", command_path);
			else
				run(command_path, shell->input, shell->environ);
		}
		if (exec_paths)
			free_string_array(exec_paths);
		free(command_path);
	}
}

/*
** DESCRIPTION:
** This function takes the name of a binary and the path
** of a directly and looks for the binary in it.
**
** RETURN VALUE:
** If the binary is found, the absolute path of the binary
** is returned. Otherwise, NULL is returned.
*/

char	*search_command(char *name, char *exec_path)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	char			path[1024];

	ft_strcpy(path, exec_path);
	ft_strcat(path, "/");
	pdir = opendir(exec_path);
	if (!pdir)
		return (NULL);
	while ((pdirent = readdir(pdir)) != NULL)
	{
		if (ft_strcmp(pdirent->d_name, name) == 0 && pdirent->d_type != DT_DIR)
		{
			ft_strcat(path, pdirent->d_name);
			if (access(path, X_OK) != -1)
			{
				closedir(pdir);
				return (ft_strdup(path));
			}
			ft_bzero(path + ft_strlen(exec_path) + 1,
			ft_strlen(pdirent->d_name));
		}
	}
	closedir(pdir);
	return (NULL);
}

/*
** DESCRIPTION:
** This function takes the name of the binary to be run
** as well as the directories specified in PATH to look
** for the correct binary and run it.
** Binaries can be run in three ways:
** 1) The absolute path of the binary is given.
** 2) The relative path of the binary is given (./binary).
** 3) The binary name is given and it is located in
** one of the directories specified in PATH.
**
** RETURN VALUE:
** If the binary is found and is valid, the absolute path of
** the binary is returned. Otherwise, NULL is returned.
*/

char	*find_command(char *name, char **exec_paths)
{
	int		i;
	char	*command_path;

	i = 0;
	if (ft_strlen(name) >= 3 && contains(name, '/') == 1)
		if (name[0] == '.' && name[1] == '/')
			if (access(name, F_OK) != -1 && access(name, X_OK) != -1)
				return (ft_strdup(name));
	if (ft_strlen(name) >= 3 && contains(name, '/'))
		if (name[0] == '/')
			if (access(name, F_OK) != -1 && access(name, X_OK) != -1)
				return (ft_strdup(name));
	if (!contains(name, '/') && exec_paths)
		while (exec_paths[i])
		{
			command_path = search_command(name, exec_paths[i]);
			if (command_path)
				return (command_path);
			i++;
		}
	return (NULL);
}
