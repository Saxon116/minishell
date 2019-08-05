/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:04:45 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/05 17:57:23 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function allocates and initializes a new instance of
** the shell struct.
**
** RETURN VALUE:
** If the allocation succeeds, the new instance of a shell
** struct is returned. Otherwise, 0 is returned.
*/
t_shell *init_shell()
{
	t_shell *shell;
	char cwd[1024];
	extern char **environ;

	if((shell = malloc(sizeof(t_shell))) == NULL)
		return (0);
	shell->environ = string_arr_cpy(environ);
	shell->home = ft_getenv(shell, "HOME");
	getcwd(cwd, 1024);
	shell->pwd = ft_strdup(cwd);
	shell->oldpwd = ft_strdup(cwd);
	return (shell);
}

/*
** DESCRIPTION:
** This function displays the minishell prompt which contains
** the current working directory. If the HOME directory is found
** in the CWD, it is replaced by tilde.
*/
void display_prompt(t_shell *shell)
{
	char cwd[1024];
	char *cwd_home;

	getcwd(cwd, 1024);
	cwd_home = replace_substring(cwd, shell->home, "~");
	free(shell->home);
	shell->home = NULL;
	ft_printf(LIGHTBLUE"%s >"RESET" ", cwd_home);
	free(cwd_home);
}

/*
** DESCRIPTION:
** This function frees the contents of the shell struct as
** well as the struct itself.
*/
void free_shell_vars(t_shell *shell)
{
	if(shell->home)
		free(shell->home);
	if(shell->pwd)
		free(shell->pwd);
	if(shell->oldpwd)
		free(shell->oldpwd);
	if(shell->environ)
		free_string_array(shell->environ);
	if(shell->input)
		free_string_array(shell->input);
	free(shell);
}

/*
** DESCRIPTION:
** This function executes the binary given to it with
** the args and environment variables specified. It will
** create a new child process with fork() to execute the
** binary. Once the binary is done running, the process
** is terminated. The parent process will wait for the
** child process to finish by using waitpid().
*
** RETURN VALUE:
** If the new process was created succesfully, 1 is returned.
** Otherwise, 0 is returned.
*/
int run(char *filename, char **args, char **environ)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(filename, args, environ) == -1)
			ft_printf("Error while executing command.\n");
		exit(0);
	}
	else if (pid < 0)
	{
		ft_printf("Error creating new process.\n");
		return (0);
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}
