/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:59:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/02 17:04:59 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *replace_substring(char *str, char *substr, char *rep)
{
	char *start;
	char *middle;
	char *newstr;
	int index_substr;

	if(!str || !substr || !rep)
		return (ft_strdup(str));
	index_substr = ft_strstr(str, substr) - str;
	if(ft_strcmp(str, substr) == 0)
		return (ft_strdup(rep));
	if(!ft_strstr(str, substr))
		return (ft_strdup(str));
	if(index_substr == 0)
		return (ft_strjoin(rep, str + ft_strlen(substr)));
	start = ft_strsub(str, 0, index_substr);
	middle = ft_strjoin(start, rep);
	newstr = ft_strjoin(middle, str + index_substr + ft_strlen(substr));
	free(start);
	free(middle);
	return (newstr);
}

void free_string_array(char **array)
{
	int i;

	i = 0;
	if(array)
	{
		while(array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

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
	char *cwd_home;
	extern char **environ;

	if((shell = malloc(sizeof(t_shell))) == NULL)
		return (0);
	shell->environ = string_arr_cpy(environ);
	shell->home = ft_getenv(shell, "HOME");
	getcwd(cwd, 1024);
	shell->pwd = ft_strdup(cwd);
	shell->oldpwd = ft_strdup(cwd);
	cwd_home = replace_substring(cwd, shell->home, "~");
	free(shell->home);
	ft_printf(YELLOWBLUE"%s -->"RESET" ", cwd_home);
	while(1)
	{
		if(get_next_line(0, &line))
		{
			shell->input = ft_strsplit(line, " \t");
			free(line);
			free(cwd_home);
			shell->home = ft_getenv(shell, "HOME");
			if(shell->input[0])
				parse_command(shell);
			free_string_array(shell->input);
			getcwd(cwd, 1024);
			cwd_home = replace_substring(cwd, shell->home, "~");
			free(shell->home);
			shell->home = NULL;
			ft_printf(YELLOWBLUE"%s -->"RESET" ", cwd_home);
		}
	}
	return 0;
}
