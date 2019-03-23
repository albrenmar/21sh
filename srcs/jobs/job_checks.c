/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/24 00:35:15 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				put_job_in_foreground(t_jobs *job, int cont)
{
	tcsetpgrp(g_tracking.sterminal, job->jpid);
	if (cont)
	{
		tcsetattr(g_tracking.sterminal, TCSADRAIN, &job->jterm);
		kill(-job->jpid, SIGCONT);
	}
	wait_for_job(job);
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
	tcgetattr(g_tracking.sterminal, &job->jterm);
}

void				put_job_in_background(t_jobs *job, int cont)
{
	if (cont)
		kill(-job->jpid, SIGCONT);
}

void				interactive_check_set_shell_group(void)
{
	g_tracking.sterminal = STDIN_FILENO;
	g_tracking.interactive = isatty(g_tracking.sterminal);
	if (g_tracking.interactive)
	{
		while (tcgetpgrp(g_tracking.sterminal) != (g_tracking.spid = getpgrp()))
			kill(-g_tracking.spid, SIGTTIN);
	}
	g_tracking.spid = getpid();
	if (setpgid(g_tracking.spid, g_tracking.spid) < 0)
	{
		ft_putendl_fd("Couldn't put the shell in its own process group", 2);
		ft_exit(1, EXIT_FAILURE);
	}
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
}

int					job_is_done(t_jobs *job)
{
	t_comm			*p;

	p = job->t_command;
	while (p)
	{
		if (p->done == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int					job_is_stopped(t_jobs *job)
{
	t_comm			*p;

	p = job->t_command;
	while (p)
	{
		if (p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
