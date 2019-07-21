/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:17:27 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/21 17:05:10 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		num_of_words(char *s, char *chars)
{
	int words;
	int i;
	int isword;

	i = 0;
	isword = 0;
	words = 0;
	while (s[i])
	{
		if (contains(chars, s[i]))
			isword = 0;
		else if (!isword)
		{
			words++;
			isword = 1;
		}
		i++;
	}
	return (words);
}

static int		wordindex(char *s, char *chars, int n)
{
	int words;
	int i;
	int isword;

	i = 0;
	isword = 0;
	words = -1;
	while (s[i])
	{
		if (contains(chars, s[i]))
			isword = 0;
		else if (!isword)
		{
			words++;
			isword = 1;
		}
		if (words == n)
			return (i);
		i++;
	}
	return (-1);
}

static int		wordlen(char *s, char *chars, int n)
{
	int i;
	int length;

	length = 0;
	i = wordindex(s, chars, n);
	while (!contains(chars, s[i + length]) && s[i + length])
		length++;
	return (length);
}

char			**ft_strsplit(char const *s, char *chars)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || (array = malloc(sizeof(char *) *
	num_of_words((char *)s, chars) + 1)) == NULL)
		return (0);
	while (i < num_of_words((char *)s, chars))
	{
		if ((array[i] = malloc(sizeof(char) *
		wordlen((char *)s, chars, i) + 1)) == NULL)
			return (0);
		j = 0;
		while (j < wordlen((char *)s, chars, i))
		{
			array[i][j] = s[wordindex((char *)s, chars, i) + j];
			j++;
		}
		array[i][j] = '\0';
		i++;
	}
	array[i] = 0;
	return (array);
}
