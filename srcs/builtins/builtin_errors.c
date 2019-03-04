/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/03 11:45:00 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

// int			errors_cd(char **tab_exec, int error)
// {
// 	if (error == 0)
// 	{
// 		ft_putstr_fd(SHELL_NAME, 2);
// 		ft_putstr_fd(": cd: ", 2);
// 		ft_putendl_fd(" too many arguments", 2);
// 	}
// }

int			errors_hash(char *binary, int error)
{
	if (error == 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl_fd(": hash table empty", 2);
	}
	if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": hash: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putendl_fd(" not found", 2);
	}
	return (-1);
}

int			errors_fg(int nb, int error)
{
	if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl_fd(": fg: wrong job_id usage, only one job supported ", 2);
	}
	if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": fg: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
		return (1);
	}
	else if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": fg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	return (1);
}

int			errors_bg(int nb, int error)
{
	if (error == 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": bg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" is already in the background!", 2);
	}
	if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl_fd(": bg: wrong job_id usage, only one job supported ", 2);
	}
	if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": bg: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
		return (1);
	}
	else if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": bg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	return (1);
}

int			errors_jobs(char option, int nb, int error)
{
	if (error == 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": jobs: ", 2);
		ft_putendl_fd("wrong options usage", 2);
		ft_putendl_fd("jobs: usage: jobs [-lp] [\%jobid ...]", 2);
	}
	else if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": jobs: -", 2);
		ft_putchar_fd(option, 2);
		ft_putstr_fd(": invalid option", 2);
		ft_putendl_fd("jobs: usage: jobs [-lp] [\%jobid ...]", 2);
	}
	else if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": jobs: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": jobs: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
		return (1);
	}
	return (1);
}
