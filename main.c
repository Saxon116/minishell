/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:59:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/25 17:19:50 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void print_char_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

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

int main()
{
	char *line;
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
	ft_printf(YELLOWBLUE"%s --> "RESET, cwd);
	while(1)
	{
		if(get_next_line(0, &line))
		{
			char **input = ft_strsplit(line, " \t");
			if(input[0])
				parse_command(input, shell);
			getcwd(cwd, 1024);
			ft_printf(YELLOWBLUE"%s --> "RESET, cwd);
		}
		free(line);
	}
	return 0;
}
