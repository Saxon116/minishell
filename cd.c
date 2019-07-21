/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:38:51 by nkellum           #+#    #+#             */
/*   Updated: 2019/07/21 17:06:15 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_lstat_path(char *path, char *name)
{
  return (ft_strsub(path, 0, ft_strstr(path, name) - path + ft_strlen(name)));
}

int check_new_wd(char *first_dir, int index, char **dirs, char *path)
{
  DIR *pdir;
	struct dirent *pdirent;
	struct stat		pstat;
  char *name;

  pdir = opendir(first_dir ? first_dir : dirs[index]);
  name = first_dir ? dirs[0] : dirs[index + 1];
  if(!name)
    return (1);
	if(!pdir)
	 return (0);
	while ((pdirent = readdir(pdir)) != NULL)
		if (ft_strcmp(pdirent->d_name, name) == 0 && pdirent->d_type == DT_DIR)
		{
			if (lstat(get_lstat_path(path, name), &pstat) == -1)
				return (0);
			if(pstat.st_mode & S_IXUSR)
				return (!dirs[index + 1] ? 1 : check_new_wd(NULL, index + (!first_dir), dirs, path));
      else
        return (-1);
		}
	return (0);
}

int cd(char **input, char **environ)
{
	char *path;
	int i;
  int status;

	i = 0;
  if(input[2])
  {
    ft_printf("minishell: cd: too many arguments\n");
    return (0);
  }
	if(input[1])
  {
    status = check_new_wd(input[1][0] == '/' ? "/" : "." ,
    0, ft_strsplit(input[1], "/"), input[1]);
		if (status > 0)
      chdir(input[1]);
    else
    {
      if(status == 0)
        ft_printf("minishell: cd: %s: No such file or directory\n", input[1]);
      if(status == -1)
        ft_printf("minishell: cd: %s: Permission denied\n", input[1]);
      return (0);
    }
  }
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
