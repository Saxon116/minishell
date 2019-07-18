/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:38:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/18 23:04:17 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_folder(char *path)
{
  int i;

  i = 0;
  while(path[i])
  {
    if (path[i] == '/')
      break ;
    i++;
  }
  if(!path[i + 1])
    return (0);
  else
    return (1);
}

char *get_cwd_name(char *path)
{
  int i;
  int length;

  length = 0;
  i = 0;
  if(path[0] == '/')
    return (ft_strdup("/"));
  while(path[i])
  {
    if (path[i] != '/')
      length++;
    i++;
  }
  return (ft_strsub(path, 0, length));
}

int check_new_wd(char *path)
{
  DIR *pdir;
	struct dirent *pdirent;
	struct stat		pstat;
  char *name;

  name = get_cwd_name(path);
	pdir = opendir(name);
  ft_printf("name is %s\n", name);
  while(!last_folder(path) && *path != '/')
    path++;
  free(name);
  name = get_cwd_name(path + (!last_folder(path)));
	if(!pdir)
	 return (0);
	while ((pdirent = readdir(pdir)) != NULL)
	{
    ft_printf("name is %s d_name is %s\n", name, pdirent->d_name);
		if (ft_strcmp(pdirent->d_name, name) == 0 && pdirent->d_type == DT_DIR)
		{
      ft_printf("made it in here\n");
      free(name);
			if (lstat(path, &pstat) == -1)
				return (0);
			if(pstat.st_mode & S_IXUSR)
				return (last_folder(path) ? 1 : check_new_wd(path));
      else
        return (-1);
		}
	}
	return (5);
}

int cd(char **input, char **environ)
{
	char *path;
	int i;

	i = 0;
	if(input[1])
		ft_printf("%d\n", check_new_wd(input[1]));
	else
	{
		path = ft_getenv("HOME", environ);
		if(!path)
		{
			ft_printf("HOME environment variable not defined.\n");
			return (0);
		}
		while(path[i] != '=')
			i++;
		if(!path[i + 1])
		{
			ft_printf("HOME environment variable is empty.\n");
			return (0);
		}
		chdir(path + i + 1);
	}
	return (1);
}
