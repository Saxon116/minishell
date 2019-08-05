/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:06:57 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/05 15:07:12 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void print_string_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}
