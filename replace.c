/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:42:31 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 12:42:02 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function replaces any tilde symbols in the arguments sent
** to minishell with the value of the HOME environment variable.
**
** RETURN VALUE:
** If HOME is not set or there are not arguments, NULL is returned.
** Otherwise, a new array is returned with the tilde characters
** replaced by the value of HOME.
**
** EXTERNAL FUNCTIONS:
** check_env is located in env.c
*/

char	**replace_tilde(t_shell *shell, char **input)
{
	int		i;
	int		length;
	char	**new_array;

	length = 0;
	while (input[length])
		length++;
	if (length < 2)
		return (NULL);
	i = 1;
	new_array = string_arr_cpy(input);
	while (input[i])
	{
		free(new_array[i]);
		if (contains(input[i], '~') && check_env(shell, "HOME") == -1)
		{
			ft_printf("HOME not set.\n");
			return (NULL);
		}
		new_array[i] = replace_substring(input[i], "~", shell->home);
		i++;
	}
	return (new_array);
}

/*
** DESCRIPTION:
** This function checks if the dollar symbol is found in any
** strings of the string array.
**
** RETURN VALUE:
** If the dollar symbol is found, 1 is returned. Otherwise, 0 is returned.
*/

int		contains_dollar(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (contains(input[i], '$'))
			return (1);
		i++;
	}
	return (0);
}

/*
** DESCRIPTION:
** This function replaces the name of an environment variable
** in front of a dollar symbol with the variable's value in
** every string of input.
**
** RETURN VALUE:
** If no dollar symbols are found or there are not arguments, NULL is
** returned. Otherwise, a new array is returned with $ENVNAME replaced
** with their values.
**
** EXTERNAL FUNCTIONS:
** ft_getenv is located in env.c
*/

char	**replace_dollar_env(t_shell *shell, char **input)
{
	int		i;
	int		length;
	char	**new_array;

	length = 0;
	while (input[length])
		length++;
	if (!contains_dollar(input) || length < 2)
		return (NULL);
	i = 1;
	new_array = string_arr_cpy(input);
	while (input[i])
	{
		if (ft_strlen(input[i]) > 1 && input[i][0] == '$')
		{
			if (check_env(shell, input[i] + 1) != -1)
			{
				free(new_array[i]);
				new_array[i] = ft_getenv(shell, input[i] + 1);
			}
		}
		i++;
	}
	return (new_array);
}
