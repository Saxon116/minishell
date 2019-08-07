/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:38:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 12:01:10 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function updates the OLDPWD and PWD environment variables
** when the current working directory is changed.
** If they exist they will be edited, if they do not they will be
** created.
**
** EXTERNAL FUNCTIONS:
** add_env_var is located in edit_env.c
*/

void	update_pwds(t_shell *shell)
{
	char	concat[1024];

	ft_bzero(concat, 1024);
	ft_strcpy(concat, "OLDPWD=");
	ft_strcat(concat, shell->oldpwd);
	add_env_var(shell, concat);
	ft_bzero(concat, 1024);
	ft_strcpy(concat, "PWD=");
	ft_strcat(concat, shell->pwd);
	add_env_var(shell, concat);
}

/*
** DESCRIPTION:
** This function changes the current working directory
** if the path specified exists and is executable.
*/

void	change_dir(t_shell *shell)
{
	char	cwd[1024];

	if (access(shell->input[1], F_OK) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n",
		shell->input[1]);
		return ;
	}
	if (access(shell->input[1], X_OK) == -1)
	{
		ft_printf("minishell: cd: %s: Permission denied\n", shell->input[1]);
		return ;
	}
	chdir(shell->input[1]);
	getcwd(cwd, 1024);
	free(shell->oldpwd);
	shell->oldpwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	shell->pwd = ft_strdup(cwd);
	update_pwds(shell);
}

/*
** DESCRIPTION:
** This function checks if the argument passed to cd is
** a dash. If it is, PWD will be set to OLWDPWD and
** vice versa. Otherwise, it will call change_dir
** to check if the new PWD path is valid before
** changing it.
*/

void	check_and_cd(t_shell *shell)
{
	char	*temp;

	if (ft_strcmp(shell->input[1], "-") == 0)
	{
		temp = ft_strdup(shell->oldpwd);
		free(shell->oldpwd);
		shell->oldpwd = ft_strdup(shell->pwd);
		free(shell->pwd);
		shell->pwd = ft_strdup(temp);
		free(temp);
		update_pwds(shell);
		ft_printf("%s\n", shell->pwd);
		chdir(shell->pwd);
	}
	else
		change_dir(shell);
}

/*
** DESCRIPTION:
** This function is called when no arguments are
** passed to cd. In this case, cd will change
** the current working directory to HOME if
** it is set. If it is not, an error message
** is displayed.
*/

void	cd_home(t_shell *shell)
{
	char	*path;

	path = ft_getenv(shell, "HOME");
	if (!path)
	{
		ft_printf("HOME environment variable not defined.\n");
		return ;
	}
	chdir(path);
	free(shell->oldpwd);
	shell->oldpwd = ft_strdup(shell->pwd);
	free(shell->pwd);
	shell->pwd = ft_strdup(path);
	free(path);
	update_pwds(shell);
}

/*
** DESCRIPTION:
** This function changes the current working directory of
** minishell by parsing through the arguments passed to it
** and calling the appropriate functions above.
**
** RETURN VALUE:
** On success, 1 is returned. On error, 0 is returned.
*/

int		cd(t_shell *shell)
{
	int	length;

	length = 0;
	while (shell->input[length])
		length++;
	if (length >= 3)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (0);
	}
	if (length == 2)
		check_and_cd(shell);
	else
		cd_home(shell);
	return (1);
}
