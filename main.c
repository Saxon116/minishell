/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:59:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 12:40:17 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** Minishell is a simple shell that interprets unix commands
** and includes basic builtin commands such as cd, echo,
** setenv, unsetenv, and exit.
**
** EXTERNAL FUNCTIONS:
** display_prompt is located in shell.c
** init_shell is located in shell.c
** ft_getenv is located in env.c
*/

int	main(void)
{
	char	*line;
	t_shell	*shell;

	shell = init_shell();
	display_prompt(shell);
	while (1)
	{
		if (get_next_line(0, &line))
		{
			shell->input = ft_strsplit(line, " \t");
			free(line);
			shell->home = ft_getenv(shell, "HOME");
			if (shell->input[0])
				parse_command(shell);
			free_string_array(shell->input);
			display_prompt(shell);
		}
	}
	return (0);
}
