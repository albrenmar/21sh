/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/22 06:54:22 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			fg_builtin_output(t_jobs *tmp)
{
	ft_putendl(tmp->name);
	tmp->background = 0;
	continue_job(tmp, 1);
	return (0);
}

int			fg_exists(t_jobs *tmp, int mode)
{
	int		nb;

	nb = 0;
	if (mode == 1)
	{
	while (tmp->prev)
		tmp = tmp->prev;
	nb = parse_job_sign(g_tracking.g_tab_exec[1]);
	while (tmp->next && tmp->place != nb)
		tmp = tmp->next;
	if (nb == 0)
		return (errors_fg(0, 2));
	else if (nb != 0)
		return (fg_builtin_output(tmp));
	}
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next && tmp->place != nb)
		tmp = tmp->next;
	return (fg_builtin_output(tmp));
}

int			fg_builtin(void)
{
	t_jobs	*tmp;
	char	*hold;
	int		nb;

	nb = 0;
	tmp = g_tracking.jobs;
	if (tmp->next)
	{
		if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] == '%')
		{
			hold = parse_job_number(g_tracking.g_tab_exec[1]);
			if (hold)
				nb = ft_atoi(hold);
			if (job_exists(parse_job_sign(g_tracking.g_tab_exec[1])))
				return (fg_exists(tmp, 1));
			else if (hold && job_exists(ft_atoi(hold)))
				return (fg_exists(tmp, 2));
			else if (hold)
				return (errors_fg(ft_atoi(hold), 3));
			else
				errors_fg(0, 2);
		}
		else if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] != '%')
			return (errors_fg(tmp->place, 2));
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp->next && tmp->current != 1)
			tmp = tmp->next;
		return (fg_builtin_output(tmp));
	}
	errors_fg(0, 4);
	return (1);
}
