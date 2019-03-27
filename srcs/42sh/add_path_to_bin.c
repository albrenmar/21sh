/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:00:43 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/27 09:20:06 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int					test_exist_fonction_two(char ***tab_cmd, char **pathlist)
{
	int				i;
	char			*next_str;
	char			*addslash;

	i = 0;
	next_str = NULL;
	if (!pathlist)
		return (0);
	while (pathlist[i])
	{
		addslash = ft_strjoin(pathlist[i], "/");
		next_str = ft_strjoin(addslash, *tab_cmd[0]);
		if (access(next_str, X_OK) == 0)
		{
			free(*tab_cmd[0]);
			*tab_cmd[0] = ft_strdup(next_str);
			free(addslash);
			free(next_str);
			return (1);
		}
		i++;
		free(addslash);
		free(next_str);
	}
	return (0);
}

void				freeing_paths(char *path, char **pathlist)
{
	ft_strdel(&path);
	free_tab(pathlist);
}

char				**exist_help(char **t, char *p, char **pl, struct stat s)
{
	if (t[0][0] == '/' || (t[0][0] == '.'
	&& t[0][1] == '/' && S_ISREG(s.st_mode)))
		return (t);
	p = ft_strdup(get_env_string("PATH"));
	pl = ft_strsplit(p, ':');
	if (test_exist_fonction_two(&t, pl) == 1)
	{
		freeing_paths(p, pl);
		return (t);
	}
	freeing_paths(p, pl);
	return (NULL);
}

char				**test_exist_fonction(char **tab_cmd, int mode)
{
	char			**pathlist;
	char			*path;
	struct stat		path_stat;

	stat(tab_cmd[0], &path_stat);
	path = NULL;
	pathlist = NULL;
	if (ft_strchr(tab_cmd[0], '/') && S_ISREG(path_stat.st_mode) == 0)
		return (NULL);
	if (mode == 1)
	{
		path = ft_strdup(get_env_string("PATH"));
		pathlist = ft_strsplit(path, ':');
		if (test_exist_fonction_two(&tab_cmd, pathlist) == 1)
		{
			freeing_paths(path, pathlist);
			return (tab_cmd);
		}
		freeing_paths(path, pathlist);
		return (NULL);
	}
	else
		return (exist_help(tab_cmd, path, pathlist, path_stat));
	freeing_paths(path, pathlist);
	return (NULL);
}
