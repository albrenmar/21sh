/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 05:52:52 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		mark_job_as_running(t_jobs *job)
{
	t_comm	*cmd;

	cmd = job->t_command;
	while (cmd)
	{
		cmd->stopped = 0;
		cmd = cmd->next;
	}
	job->notified = 0;
}

void		continue_job(t_jobs *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}

void		jobs_notifications(void)
{
	t_jobs	*job;
	t_jobs	*joblast;
	t_jobs	*jobnext;

	update_status();
	joblast = NULL;
	job = g_tracking.jobs;
	while (job)
	{
		jobs_notifications_output(job);
		jobnext = job->next;
		if (job_is_done(job))
			jobs_notif_h(job, joblast, jobnext, 0);
		else if (job_is_stopped(job) && !job->notified)
		{
			show_job_info(job, "Stopped                ", 2, 0);
			job->notified = 1;
			joblast = job;
		}
		else
			joblast = job;
		job = jobnext;
	}
}

void		show_job_info(t_jobs *job, const char *status, int mode, int s)
{
	if (mode)
		show_job_info_helper(job, mode);
	else
	{
		ft_putnbr(job->jpid);
		ft_putstr("   ");
	}
	ft_putstr(status);
	if (mode == 4)
	{
		ft_putchar('(');
		ft_putnbr(s);
		ft_putchar(')');
		ft_putstr("           ");
	}
	if (mode == 3)
	{
		ft_putstr("by signal: ");
		ft_putnbr(WTERMSIG(job->t_command->status));
	}
	ft_putchar(' ');
	ft_putendl(job->name);
}
