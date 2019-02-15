/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/14 22:09:26 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define ORDER g_tracking.mysh->order

void		execute_two(t_env *st_env, int mode, t_jobs *job)
{
	char	**envtab;
	pid_t	pid0;
	
	envtab = envlist_to_tab(&st_env);
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
			if ((ORDER->command = test_exist_fonction(ORDER->command)))
				execve(ORDER->command[0], ORDER->command, envtab);
			else
				exit(-1);
		}
		else if (mode == 2)
		{

			close(descrf[1]);
			dup2(descrf[0], 0);
			close(descrf[0]);
			if ((ORDER->command = test_exist_fonction(ORDER->command)))
				execve(ORDER->command[0], ORDER->command, envtab);
			else
				exit(-1);
		}
	}
	else
	{
		if (mode == 2)
			close(descrf_two[1]);
		new_process(job, pid0);
		// if (mode == 2)
		// 	job->lastpid = pid0;
		if (job->jpid == 0)
			job->jpid = pid0;
		setpgid(pid0, job->jpid);
	}
}

void		execute_pipe(t_env *st_env, t_jobs *job)
{
	execute_two(st_env, 0, job);
}
