/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:37:25 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/28 21:22:26 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** DESCRIPTION:
** This function is only used in this file, and it checks if an
** environment variable exists by taking the VAR_NAME=value format,
** isolating the name, and calling check_env.
**
** RETURN VALUE:
** If the variable exists, the function will return the index of
** the variable's position in the array. Otherwise -1 is returned
** since the returned value could be the 0th element of the array.
**
** EXTERNAL FUNCTIONS:
** check_env function is located in env.c
*/
int check_env_with_val(t_shell *shell, char *var)
{
	int i;
	char *name;

	i = 0;
	while(var[i])
	{
		if(var[i] == '=')
		break;
		i++;
	}
	name = ft_strsub(var, 0, i);
	i = check_env(shell, name);
	free(name);
	return (i);
}

/*
** DESCRIPTION:
** This function changes the value of an existing environment
** variable by taking the name and value to be overwritten.
** If value is NULL, the function will assume that
** the name parameter has the value within it in the
** "NAME=value" format.
**
** EXTERNAL FUNCTIONS:
** check_env function is located in env.c
*/
void set_existing_var(t_shell *shell, char *name, char* value)
{
	char var[1024];
	int index;

	ft_bzero(var, 1024);
	index = value ? check_env(shell, name) : check_env_with_val(shell, name);
	if(index != -1)
	{
		if(value)
		{
			ft_strcpy(var, name);
			ft_strcat(var, "=");
			ft_strcat(var, value);
			free(shell->environ[index]);
			shell->environ[index] = ft_strdup(var);
		}
		else
		{
			free(shell->environ[index]);
			shell->environ[index] = ft_strdup(name);
		}
	}
}

/*
** DESCRIPTION:
** This function deletes an existing environment variable. The index
** represents the position of the value to be deleted in the array.
** A new string array is allocated without that value and returned.
*/
void del_env_var(t_shell *shell, int index)
{
	char **new_array;
	int length;
	int i;
	int j;

	length = 0;
	i = 0;
	j = 0;
	while(shell->environ[length])
		length++;
	if((new_array = malloc(sizeof(char**) * length)) == NULL)
		return ;
	while(i < length - 1)
	{
		if(j == index)
			j++;
		new_array[i] = ft_strdup(shell->environ[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
	free(shell->environ);
	shell->environ = new_array;
}

/*
** DESCRIPTION:
** This function adds a new environment variable, or edits a variable
** if it already exists by calling set_existing_var. A string in the
** "VAR_NAME=value" format should be passed in var.
*/
void add_env_var(t_shell *shell, char *var)
{
	char **new_array;
	int length;
	int i;

	length = 0;
	i = 0;
	if(check_env_with_val(shell, var) != -1)
		set_existing_var(shell, var, NULL);
	else
	{
		while(shell->environ[length])
			length++;
		if((new_array = malloc(sizeof(char**) * (length + 2))) == NULL)
			return ;
		while(i < length)
		{
			new_array[i] = ft_strdup(shell->environ[i]);
			i++;
		}
		new_array[i] = ft_strdup(var);
		new_array[length + 1] = NULL;
		free(shell->environ);
		shell->environ = new_array;
	}
}

/*
** DESCRIPTION:
** This function returns a newly allocated copy of the string array
** passed into it.
**
** RETURN VALUE:
** On success, the copy of the string array. On error, NULL is returned.
*/
char **string_arr_cpy(char **array)
{
	char **new_array;
	int length;
	int i;

	length = 0;
	i = 0;
	while(array[length])
		length++;
	if((new_array = malloc(sizeof(char *) * (length + 1))) == NULL)
		return (NULL);
	while(i < length)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = 0;
	return (new_array);
}
