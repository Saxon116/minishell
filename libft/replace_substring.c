/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_substring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:05:34 by nkellum           #+#    #+#             */
/*   Updated: 2019/08/07 11:45:07 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*replace_substring(char *str, char *substr, char *rep)
{
	char	*start;
	char	*middle;
	char	*newstr;
	int		index_substr;

	if (!str || !substr || !rep)
		return (ft_strdup(str));
	index_substr = ft_strstr(str, substr) - str;
	if (ft_strcmp(str, substr) == 0)
		return (ft_strdup(rep));
	if (!ft_strstr(str, substr))
		return (ft_strdup(str));
	if (index_substr == 0)
		return (ft_strjoin(rep, str + ft_strlen(substr)));
	start = ft_strsub(str, 0, index_substr);
	middle = ft_strjoin(start, rep);
	newstr = ft_strjoin(middle, str + index_substr + ft_strlen(substr));
	free(start);
	free(middle);
	return (newstr);
}
