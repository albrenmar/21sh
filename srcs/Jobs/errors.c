/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/25 15:45:20 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			errors_hash(char *binary, int error)
{
	if (error == 0)
	{
		ft_putendl_fd("42sh: hash table empty", 2);
	}
	if (error == 1)
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putendl_fd(" not found", 2);
	}
	return (-1);
}

int			errors_fg(int nb, int error)
{
	// if (error == 0)
	// {
	// 	ft_putstr("42sh: fg: job ");
	// 	ft_putnbr(nb);
	// 	ft_putendl(" is already in the background!");
	// }
	if (error == 1)
		ft_putendl("42sh: fg: wrong job_id usage, only one job supported ");
	if (error == 2)
	{
		ft_putstr("42sh: fg: ");
		ft_putendl("wrong job_id usage");
		return (1);
	}
	else if (error == 3)
	{
		ft_putstr("42sh: fg: job ");
		ft_putnbr(nb);
		ft_putendl(" doesn't exist!");
	}
	return (1);
}

int			errors_bg(int nb, int error)
{
	if (error == 0)
	{
		ft_putstr("42sh: bg: job ");
		ft_putnbr(nb);
		ft_putendl(" is already in the background!");
	}
	if (error == 1)
		ft_putendl("42sh: bg: wrong job_id usage, only one job supported ");
	if (error == 2)
	{
		ft_putstr("42sh: bg: ");
		ft_putendl("wrong job_id usage");
		return (1);
	}
	else if (error == 3)
	{
		ft_putstr("42sh: bg: job ");
		ft_putnbr(nb);
		ft_putendl(" doesn't exist!");
	}
	return (1);
}

int			errors_jobs(char option, int nb, int error)
{
	if (error == 0)
	{
		ft_putstr("42sh: jobs: ");
		ft_putendl("wrong options usage");
		ft_putendl("jobs: usage: jobs [-lp] [\%jobid ...]");
	}
	else if (error == 1)
	{
		ft_putstr("42sh: jobs: -");
		ft_putchar(option);
		ft_putstr(": invalid option");
		ft_putendl("jobs: usage: jobs [-lp] [\%jobid ...]");
	}
	else if (error == 2)
	{
		ft_putstr("42sh: jobs: job ");
		ft_putnbr(nb);
		ft_putendl(" doesn't exist!");
	}
	if (error == 3)
	{
		ft_putstr("42sh: jobs: ");
		ft_putendl("wrong job_id usage");
		return (1);
	}
	return (1);
}
