/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/07 03:47:27 by abguimba         ###   ########.fr       */
=======
/*   Updated: 2019/03/01 08:09:20 by abguimba         ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		execute_two(char **tab_exec)
{
	char	**tab_exec_hold;

<<<<<<< HEAD
	clean_tab_exec(tab_exec);
=======
>>>>>>> alsomvil
	tab_exec_hold = tab_dup(tab_exec);
	if (is_builtin())
		exit (builtin_exec(NULL));
	if ((tab_exec = hashed_command(tab_exec)))
	{
		execve(tab_exec[0], tab_exec, NULL);
<<<<<<< HEAD
=======
		perror("FAIL");
>>>>>>> alsomvil
		exit(-1);
	}
	else if ((test_exist_fonction(tab_exec_hold, 2)))
	{
		execve(tab_exec_hold[0], tab_exec_hold, NULL);
<<<<<<< HEAD
		exec_errors(tab_exec, 0);
=======
		perror("FAIL");
>>>>>>> alsomvil
		exit(-1);
	}
	else
	{
<<<<<<< HEAD
		exec_errors(NULL, 1);
		free_tab(tab_exec_hold);
		exit(-1);
	}
=======
		ft_putstr_fd("La commande ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(" n'existe pas", 2);
		free_tab(tab_exec_hold);
		exit(-1);
	}
	free_tab(tab_exec_hold);
>>>>>>> alsomvil
}


void		execute_pipe_two(char **tab_exec, t_jobs *job)
{
	int		status;
	int		j;
	pid_t	pid0;

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
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
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
<<<<<<< HEAD
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
=======
		g_tracking.builtin = 1;
>>>>>>> alsomvil
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
<<<<<<< HEAD
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
=======
		g_tracking.builtin = 1;
>>>>>>> alsomvil
}
