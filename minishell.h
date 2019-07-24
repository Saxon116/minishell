/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:10:37 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/24 23:25:54 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct  s_shell
{
	char				  **environ;
	char				  *home;
}						    t_shell;


char *find_command(char *name, char **exec_paths);
void parse_command(char **input, t_shell *shell);
int run(char *filename, char **args, char **environ);
char **get_exec_paths(t_shell *shell);
int run_builtin(char **input, t_shell *shell);
int is_builtin(char *command);
int cd(char **input, t_shell *shell);
char *ft_getenv(t_shell *shell, char *name);
void print_char_array(char **array);
char **string_arr_cpy(char **array);
void add_env_var(t_shell *shell, char *var);
int check_env(t_shell *shell, char *name);










#endif
