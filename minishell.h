/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:10:37 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/12 12:28:15 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H


char *find_command(char *name, char **exec_paths);
void parse_command(char **input, char **environ);
int run(char *filename, char **args, char **environ);
char **get_exec_paths(char **environ);





#endif
