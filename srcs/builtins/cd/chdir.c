/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:00:02 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/29 05:32:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		getright(char *path, char *err)
{
	if (test_exist_dir(path) != 0)
	{
		ft_putstr(err);
		ft_putendl(": directory does not exist");
		return (1);
	}
	if (access(path, R_OK) != 0)
	{
		ft_putstr("Permission denied: ");
		ft_putendl(err);
		return (1);
	}
	return (0);
}

int		ft_changedir(char *path, char option, char *err, int i)
{
	char	*truepwd;
	char	*oldpwd;

	if ((i = getright(path, err)) == 0)
	{
		restore_env();
		truepwd = ft_true_pwd();
		replace_env_str("TRUEOLDPWD", truepwd);
		oldpwd = ft_strdup(get_env_string("PWD"));
		chdir(path);
		ft_strdel(&truepwd);
		truepwd = ft_true_pwd();
		if (option != 'P')
			replace_env_str("PWD", path);
		else
			replace_env_str("PWD", truepwd);
		replace_env_str("OLDPWD", oldpwd);
		replace_env_str("TRUEPWD", truepwd);
		ft_strdel(&truepwd);
		ft_strdel(&oldpwd);
		update_envp();
		if (option == '-')
			ft_putendl(get_env_string("PWD"));
	}
	return (i);
}
