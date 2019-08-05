/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:40:03 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/05 15:40:13 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
