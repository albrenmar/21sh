/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/21 20:50:58 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

void		execute_two(int mode, t_jobs *job, int fd)
{
	// char	**envtab;
	pid_t	pid0;
	
	// envtab = envlist_to_tab(&st_env);
	// ft_putendl("AA");
	g_tracking.orderhold = ORDER->command;
	pid0 = fork();
	if (pid0 == 0)
	{
		pid0 = getpid();
		if (job->jpid == 0)
			job->jpid = pid0;
		setpgid(pid0, job->jpid);
		if (job->background == 0)
			tcsetpgrp(g_tracking.sterminal, job->jpid);
		set_process_signal_handlers();
		if (mode == 0)
		{
			close(descrf_two[0]);
			dup2(descrf_two[1], 1);
			close(descrf_two[1]);
			close(descrf[1]);
			dup2(descrf[0], 0);
			close(descrf[0]);
			if (is_builtin(1))
				exit (builtin_exec(mode));
			else if ((ORDER->command = test_exist_fonction(ORDER->command)))
				execve(ORDER->command[0], ORDER->command, g_tracking.envtab);
			else
				exit(-1);
		}
		else if (mode == 2)
		{
			if (fd != 0)
				dup2(fd, 1);
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
			// ft_putendl("BB");
			if (is_builtin(1))
				exit (builtin_exec(mode));
			if ((ORDER->command = test_exist_fonction(ORDER->command)))
				execve(ORDER->command[0], ORDER->command, g_tracking.envtab);
			else
				exit(-1);
		}
	}
	else
	{
		if (mode == 0)
			close(descrf_two[1]);
		if (mode == 2)
			close(descrf_two[1]);
		new_process(job, pid0);
		// if (mode == 2)
		// 	job->lastpid = pid0;
		if (job->jpid == 0)
			job->jpid = pid0;
		setpgid(pid0, job->jpid);
		if (is_builtin(2))
			builtin_exec(1);
	}
}

void		execute_pipe_two(t_jobs *job, int fd)
{
	execute_two(2, job, fd);
}

void		execute_pipe(t_jobs *job)
{
	execute_two(0, job, 0);
}
