/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_arr_cpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:09:14 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 11:45:22 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**string_arr_cpy(char **array)
{
	char	**new_array;
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (array[length])
		length++;
	if ((new_array = malloc(sizeof(char *) * (length + 1))) == NULL)
		return (NULL);
	while (i < length)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = 0;
	return (new_array);
}
