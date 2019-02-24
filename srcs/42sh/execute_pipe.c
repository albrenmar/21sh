/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/23 13:35:04 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

//#define ORDER g_tracking.mysh->order
//#define EXEC g_tracking.mysh->exec

void		execute_two(char **tab_exec)
{
	if (is_builtin())
		exit (builtin_exec());
	if ((tab_exec = test_exist_fonction(tab_exec)))
	{
		execve(tab_exec[0], tab_exec, NULL);
		perror("FAIL");
	}
	else
	{
		exit(-1);
	}
}


void		execute_pipe_two(char **tab_exec, t_jobs *job)
{
	int		status;
	int		j;
	pid_t	pid0;

	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
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
			if (g_tracking.mysh->set_fd->STDIN != 0)
				dup2(g_tracking.mysh->set_fd->STDIN, 0);
			if (g_tracking.mysh->set_fd->STDOUT != 1)
				dup2(g_tracking.mysh->set_fd->STDOUT, 1);
			if (g_tracking.mysh->set_fd->STDERR != 2)
				dup2(g_tracking.mysh->set_fd->STDERR, 2);
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
			execute_two(tab_exec);
		}
		else
		{
			// waitpid(pid0, &status, WUNTRACED);
			// j = WEXITSTATUS(status);
			new_process(job, pid0);
			if (job->jpid == 0)
				job->jpid = pid0;
			setpgid(pid0, job->jpid);
		}
	/*if (j != 0)
		EXEC->ret = -1;*/
	}
	else
		g_tracking.builtin = 1;
}

void		execute_pipe(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;
	int		j;
	int		status;

	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
	pipe(descrf_two);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
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
			if (g_tracking.mysh->set_fd->STDIN != 0)
				dup2(g_tracking.mysh->set_fd->STDIN, 0);
			if (g_tracking.mysh->set_fd->STDOUT != 1)
				dup2(g_tracking.mysh->set_fd->STDOUT, 1);
			if (g_tracking.mysh->set_fd->STDERR != 2)
				dup2(g_tracking.mysh->set_fd->STDERR, 2);
			close(descrf_two[0]);
			dup2(descrf_two[1], 1);
			close(descrf_two[1]);
			close(descrf[1]);
			dup2(descrf[0], 0);
			close(descrf[0]);
			execute_two(tab_exec);
		}
		else
		{
			close(descrf_two[1]);
			// j = WEXITSTATUS(status);
			new_process(job, pid0);
			if (job->jpid == 0)
				job->jpid = pid0;
			setpgid(pid0, job->jpid);
		}
	/*if (j != 0)
		EXEC->ret = -1;*/
	}
	else
		g_tracking.builtin = 1;
}
