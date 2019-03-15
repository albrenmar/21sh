/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/15 16:36:22 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		execute_two(char **tab_exec)
{
	char	**tab_exec_hold;

	clean_tab_exec(tab_exec);
	tab_exec_hold = tab_dup(tab_exec);
	if (is_builtin())
		exit (builtin_exec(NULL));
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


void		execute_pipe_two(char **tab_exec, t_jobs *job)
{
	int		status;
	int		j;
	pid_t	pid0;

	g_tracking.g_tab_exec = tab_dup(tab_exec);
	//dprintf(2, "STDIN_EXEC = %d\n", g_tracking.mysh->set_fd->STDIN);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
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
			{
				dprintf(2, "OKMAGUEULE\n");
				dup2(g_tracking.mysh->set_fd->STDIN, 0);
			}
			if (g_tracking.mysh->set_fd->STDOUT != 1)
			{
				dprintf(2, "OKMAGUEULE22222\n");
				dup2(g_tracking.mysh->set_fd->STDOUT, 1);
			}
			if (g_tracking.mysh->set_fd->STDERR != 2)
				dup2(g_tracking.mysh->set_fd->STDERR, 2);
			if (descrf_two[0])
			{
				close(descrf_two[1]);
				dup2(descrf_two[0], 0);
				close(descrf_two[0]);
			}
			execute_two(tab_exec);
		}
		else
		{
			new_process(job, pid0);
			if (job->jpid == 0)
				job->jpid = pid0;
			setpgid(pid0, job->jpid);
		}
	}
	else
	{
		// if (g_tracking.mysh->set_fd->STDIN != 0)
		// 	dup2(g_tracking.mysh->set_fd->STDIN, 0);
		// if (g_tracking.mysh->set_fd->STDOUT != 1)
		// 	dup2(g_tracking.mysh->set_fd->STDOUT, 1);
		// if (g_tracking.mysh->set_fd->STDERR != 2)
		// 	dup2(g_tracking.mysh->set_fd->STDERR, 2);
		// close(descrf_two[1]);
		// dup2(descrf_two[0], 0);
		// close(descrf_two[0]);
		g_tracking.builtin = 1;
	}
}

void		execute_pipe(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;
	int		j;
	int		status;

	if (descrf[0])
	{
		close(descrf[0]);
		close(descrf[1]);
	}
	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
	pipe(descrf_two);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
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
			new_process(job, pid0);
			if (job->jpid == 0)
				job->jpid = pid0;
			setpgid(pid0, job->jpid);
		}
	}
	else
	{
		// if (g_tracking.mysh->set_fd->STDIN != 0)
		// 	dup2(g_tracking.mysh->set_fd->STDIN, 0);
		// if (g_tracking.mysh->set_fd->STDOUT != 1)
		// 	dup2(g_tracking.mysh->set_fd->STDOUT, 1);
		// if (g_tracking.mysh->set_fd->STDERR != 2)
		// 	dup2(g_tracking.mysh->set_fd->STDERR, 2);
		// close(descrf_two[0]);
		// dup2(descrf_two[1], 1);
		// close(descrf_two[1]);
		// close(descrf[1]);
		// dup2(descrf[0], 0);
		// close(descrf[0]);
		g_tracking.builtin = 1;
	}
}
