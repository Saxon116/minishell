/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:38:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/26 17:43:58 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **input, t_shell *shell)
{
	char *path;
	int length;
	char cwd[1024];
	char *join;

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
		if(ft_strcmp(input[1], "-") == 0)
		{
			join = ft_strdup(shell->oldpwd);
			free(shell->oldpwd);
			shell->oldpwd = ft_strdup(shell->pwd);
			free(shell->pwd);
			shell->pwd = ft_strdup(join);
			free(join);
			join = ft_strjoin("OLDPWD=", shell->oldpwd);
			add_env_var(shell, join);
			free(join);
			join = ft_strjoin("PWD=", shell->pwd);
			add_env_var(shell, join);
			free(join);
			ft_printf("%s\n", shell->pwd);
			chdir(shell->pwd);
			return (0);
		}
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
		getcwd(cwd, 1024);
		free(shell->oldpwd);
		shell->oldpwd = ft_strdup(shell->pwd);
		free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
		join = ft_strjoin("OLDPWD=", shell->oldpwd);
		add_env_var(shell, join);
		free(join);
		join = ft_strjoin("PWD=", shell->pwd);
		add_env_var(shell, join);
		free(join);
	}
	else
	{
		path = ft_getenv(shell, "HOME");
		if(!path)
		{
			ft_printf("HOME environment variable not defined.\n");
			return (0);
		}
		chdir(path);
	}
	return (1);
}
