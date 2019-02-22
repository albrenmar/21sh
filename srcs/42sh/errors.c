/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/19 06:37:11 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

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