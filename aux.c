/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:04:45 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/01 16:41:50 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **replace_dollar_env(t_shell *shell, char **input)
{
	int i;
	int length;
	char **new_array;

	length = 0;
	while(input[length])
		length++;
	if(length < 2)
		return (NULL);
	i = 1;
	new_array = string_arr_cpy(input);
	while(input[i])
	{
		if(ft_strlen(input[i]) > 1 && input[i][0] == '$')
    {
      if(check_env(shell, input[i] + 1) != -1)
      {
        free(new_array[i]);
        new_array[i] = ft_getenv(shell, input[i] + 1);
      }
    }
		i++;
	}
	return (new_array);
}
