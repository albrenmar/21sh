/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:00:43 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/18 01:36:13 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

//#define EXEC g_tracking.mysh->exec

int		test_exist_fonction_two(char ***tab_cmd, char **pathlist)
{
	int		i;
	char	*next_str;
	char	*addslash;

	i = 0;
	next_str = NULL;
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

char	**test_exist_fonction(char **tab_cmd)
{
	int		i;
	char	**pathlist;
	char	*path;

	i = 0;
	path = get_env_string("PATH");
	pathlist = ft_strsplit(path, ':');
	if ((access(tab_cmd[0], X_OK) == 0) || (test_exist_fonction_two(&tab_cmd, pathlist) == 1))
		return (tab_cmd);
	else
	{
		printf("La commande %s n'existe pas\n", tab_cmd[i]);
		//EXEC->ret = -1;
		return (NULL);
	}
	return (NULL);
}
