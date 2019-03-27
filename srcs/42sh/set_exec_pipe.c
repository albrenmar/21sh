/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:22:41 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/24 04:42:16 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		set_fd_before_exec(void)
{
	if (g_tracking.mysh->set_fd->STDIN != 0)
	{
		dup2(g_tracking.mysh->set_fd->STDIN, 0);
		close(g_tracking.mysh->set_fd->STDIN);
	}
	if (g_tracking.mysh->set_fd->STDOUT != 1)
	{
		dup2(g_tracking.mysh->set_fd->STDOUT, 1);
		close(g_tracking.mysh->set_fd->STDOUT);
	}
	if (g_tracking.mysh->set_fd->STDERR != 2)
	{
		dup2(g_tracking.mysh->set_fd->STDERR, 2);
		close(g_tracking.mysh->set_fd->STDERR);
	}
}

void		set_new_process(t_jobs *job, pid_t pid0)
{
	new_process(job, pid0);
	if (job->jpid == 0)
		job->jpid = pid0;
	setpgid(pid0, job->jpid);
}

void		set_jobs(t_jobs *job, pid_t pid0)
{
	pid0 = getpid();
	if (job->jpid == 0)
		job->jpid = pid0;
	setpgid(pid0, job->jpid);
	if (job->background == 0)
		tcsetpgrp(g_tracking.sterminal, job->jpid);
	set_process_signal_handlers();
}
