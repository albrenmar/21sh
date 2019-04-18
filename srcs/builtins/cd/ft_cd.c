/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:21:48 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:25:55 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	cd_option(char **av)
{
	if (!av[1])
		return ('n');
	if (ft_strcmp(av[1], "-P") == 0)
		return ('P');
	if (ft_strcmp(av[1], "-L") == 0)
		return ('L');
	if (ft_strcmp(av[1], "-") == 0)
		return ('-');
	if (ft_strcmp(av[1], "~") == 0)
		return ('~');
	else
		return ('n');
}

char	*home_dir(void)
{
	char	*path;

	path = ft_strdup(get_env_string("HOME"));
	if (!path)
	{
		ft_putendl("No HOME set in env");
		return (NULL);
	}
	return (path);
}

char	*prev_dir(void)
{
	char	*path;

	path = ft_strdup(get_env_string("OLDPWD"));
	if (!path)
	{
		ft_putendl("No Old PWD in env");
		return (NULL);
	}
	return (path);
}

char	*get_path(char option, char **av)
{
	if (option == '~' || !av[1])
		return (home_dir());
	if (option == '-')
		return (prev_dir());
	if (option == 'n')
		return (ft_strdup(av[1]));
	if (option != 'n' && !av[2])
		return (home_dir());
	else
		return (ft_strdup(av[2]));
}

int		ft_cd(void)
{
	char		**av;
	char		option;
	char		*path;
	char		*err;

	av = g_tracking.g_tab_exec;
	option = cd_option(av);
	path = NULL;
	path = get_path(option, av);
	if (!path)
		return (0);
	err = ft_strdup(path);
	if (path[0] != '.' && path[0] != '/')
		path = cd_path(path);
	path = sanitize_path_cd(path);
	ft_changedir(path, option, err);
	ft_free(err);
	ft_free(path);
	return (0);
}
