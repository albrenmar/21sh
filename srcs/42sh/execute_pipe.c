/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/16 19:15:51 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		execute_two(char **tab_exec)
{
	char	**tab_exec_hold;

	tab_exec_hold = tab_dup(tab_exec);
	if (is_builtin())
		exit(builtin_exec(NULL));
	if ((tab_exec = hashed_command(tab_exec)))
	{
		execve(tab_exec[0], tab_exec, NULL);
		exit(-1);
	}
	else if ((test_exist_fonction(tab_exec_hold, 2)))
	{
		execve(tab_exec_hold[0], tab_exec_hold, NULL);
		exec_errors(tab_exec, 0);
		exit(-1);
	}
	else
	{
		exec_errors(NULL, 1);
		free_tab(tab_exec_hold);
		exit(-1);
	}
}

void		set_fd_before_exec(void)
{
	if (g_tracking.mysh->set_fd->STDIN != 0)
		dup2(g_tracking.mysh->set_fd->STDIN, 0);
	if (g_tracking.mysh->set_fd->STDOUT != 1)
		dup2(g_tracking.mysh->set_fd->STDOUT, 1);
	if (g_tracking.mysh->set_fd->STDERR != 2)
		dup2(g_tracking.mysh->set_fd->STDERR, 2);
}

void		set_new_process(t_jobs *job, pid_t pid0)
{
	new_process(job, pid0);
	if (job->jpid == 0)
		job->jpid = pid0;
	setpgid(pid0, job->jpid);
}

void		close_and_dup(int mode)
{
	if (mode == 1)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
	}
	else if (mode == 2)
	{
		if (descrf_two[0])
		{
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
		}
	}
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

void		execute_pipe_two(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;

	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			set_jobs(job, pid0);
			set_fd_before_exec();
			close_and_dup(2);
			execute_two(tab_exec);
		}
		else
			set_new_process(job, pid0);
	}
	else
		g_tracking.builtin = 1;
}

void		swap_descrf(void)
{
	if (descrf[0])
	{
		close(descrf[0]);
		close(descrf[1]);
	}
	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
}

void		execute_pipe(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;

	swap_descrf();
	pipe(descrf_two);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			set_jobs(job, pid0);
			set_fd_before_exec();
			close_and_dup(1);
			execute_two(tab_exec);
		}
		else
		{
			close(descrf_two[1]);
			set_new_process(job, pid0);
		}
	}
	else
		g_tracking.builtin = 1;
}
