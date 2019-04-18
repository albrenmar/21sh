/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors_cont.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/14 23:47:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		export_errors(int mode, char *str)
{
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME": export: ", 2);
		ft_putendl_fd("too little/many arguments", 2);
	}
	else if (mode == 1)
	{
		ft_putstr_fd(SHELL_NAME": export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(SHELL_NAME" not found in local variables", 2);
	}
	return (-1);
}

int		unsetenv_errors(int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME": unsetenv: ", 2);
		ft_putendl_fd("too little/many arguments", 2);
	}
	else if (mode == 1)
	{
		ft_putstr_fd(SHELL_NAME": unsetenv: ", 2);
		ft_putendl_fd("bad formatting", 2);
	}
	return (-1);
}

int		setenv_errors(int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME": setenv: ", 2);
		ft_putendl_fd("too little/many arguments", 2);
	}
	else if (mode == 1)
	{
		ft_putstr_fd(SHELL_NAME": setenv: ", 2);
		ft_putendl_fd("bad formatting", 2);
	}
	return (-1);
}
