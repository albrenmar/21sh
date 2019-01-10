/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:08 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:31:14 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_check_arg(char **argv)
{
	t_stat	st;

	if (argv[1] && lstat(argv[1], &st) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory", 2);
		kill(0, SIGINT);
	}
}

void		ft_error(int error)
{
	if (error == 1)
	{
		ft_putendl_fd("Too much argument", 2);
		ft_putendl_fd("usage : NAME=VALUE", 2);
		return ;
	}
	if (error >= 2)
	{
		ft_putendl_fd("usage : NAME=VALUE", 2);
		return ;
	}
}

void		perm_denied(t_core *core)
{
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(MESS_DENIED, 2);
	ft_putendl_fd(core->arg[0], 2);
}

void		ft_secure_if_is_delete(t_core *core, char *dir)
{
	t_stat	s;
	char	*val;

	val = ft_strjoin(ft_getenv("PWD", core->env), "/");
	lstat(val, &s);
	if (!S_ISDIR(s.st_mode))
	{
		ft_putstr_fd(FOLDER_NOT_FOUND, 2);
		ft_putendl_fd(dir, 2);
	}
	free(val);
}

int			ft_check_args(char *args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (args[i] && args[i + 1] && args[i] == '[' &&
			(args[i + 1] == 'A' || args[i + 1] == 'B' ||
			args[i + 1] == 'C' || args[i + 1] == 'D'))
		{
			ft_putendl_fd("minishell: substitution failed", 2);
			return (ERROR);
		}
		i++;
	}
	return (TRUE);
}
