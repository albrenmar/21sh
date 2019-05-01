/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 04:57:01 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

#define expand g_tracking.expandreturn

void		set_expand_return_helper(void)
{
	if (expand == 131 || expand == 143 || expand == 137 || expand == 129
			|| expand == 134 || expand == 142 || expand == 139 || expand == 132
			|| expand == 133 || expand == 135 || expand == 138)
	{
		ft_putnbr(expand - 128);
		ft_putchar('\n');
	}
}

void		set_expand_return(void)
{
	if (expand == 131)
		ft_putstr("Quit: ");
	else if (expand == 143)
		ft_putstr("Terminated: ");
	else if (expand == 137)
		ft_putstr("Killed: ");
	else if (expand == 129)
		ft_putstr("Hang up: ");
	else if (expand == 134)
		ft_putstr("Abort trap: ");
	else if (expand == 142)
		ft_putstr("Alarm clock: ");
	else if (expand == 132)
		ft_putstr("Illegal instruction: ");
	else if (expand == 139)
		ft_putstr("Segmentation fault: ");
	else if (expand == 133)
		ft_putstr("Trace/BPT trap: ");
	else if (expand == 135)
		ft_putstr("EMT trap: ");
	else if (expand == 138)
		ft_putstr("Bus error: ");
	set_expand_return_helper();
}

void		continue_job(t_jobs *job, int foreground)
{
	t_comm	*cmd;

	cmd = job->t_command;
	while (cmd)
	{
		cmd->stopped = 0;
		cmd = cmd->next;
	}
	job->notified = 0;
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
