/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:10:37 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 12:53:58 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define BOLDMAGENTA	"\033[1;35m"
# define BOLDCYAN		"\033[1;36m"
# define BOLDWHITE		"\033[1;37m"
# define LIGHTBLUE		"\033[94m"
# define BLUEBLUE		"\033[34;46m"
# define BOLDCYANGREEN	"\033[1;36;42m"
# define REDBLACK		"\033[30;41m"

typedef struct	s_shell
{
	char		**environ;
	char		**input;
	char		*home;
	char		*pwd;
	char		*oldpwd;
}				t_shell;

char			*find_command(char *name, char **exec_paths);
void			parse_command(t_shell *shell);
int				run(char *filename, char **args, char **environ);
char			**get_exec_paths(t_shell *shell);
int				run_builtin(t_shell *shell);
int				is_builtin(char *command);
int				cd(t_shell *shell);
char			*ft_getenv(t_shell *shell, char *name);
void			print_char_array(char **array);
char			**string_arr_cpy(char **array);
void			add_env_var(t_shell *shell, char *var);
int				check_env(t_shell *shell, char *name);
void			del_env_var(t_shell *shell, int index);
int				ft_setenv(t_shell *shell);
void			set_existing_var(t_shell *shell, char *name, char *value);
void			free_shell_vars(t_shell *shell);
void			free_string_array(char **array);
char			**replace_dollar_env(t_shell *shell, char **input);
t_shell			*init_shell();
void			display_prompt(t_shell *shell);
char			**replace_tilde(t_shell *shell, char **input);

#endif
