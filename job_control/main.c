/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 00:56:21 by mjose             #+#    #+#             */
/*   Updated: 2019/01/18 05:51:37 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job	*find_job(pid_t pgid)
{
	t_job	*job_list;

	job_list = g_first_job;
	while (job_list)
	{
		if (job_list->pgid == pgid)
			return (job_list);
		job_list = job_list->next;
	}
	return (NULL);
}

int		job_is_stopped(t_job *job_list)
{
	t_process	*process_list;

	process_list = job_list->first_process;
	while (process_list)
	{
		if (!process_list->completed && !process_list->stopped)
			return (0);
		process_list = process_list->next;
	}
	return (1);
}

int		job_is_completed(t_job *job_list)
{
	t_process	*process_list;

	process_list = job_list->first_process;
	while (process_list)
	{
		if (!process_list->completed)
			return (0);
		process_list = process_list->next;
	}
	return (1);
}

void	init_shell(void)
{
	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty(g_shell_terminal);	/*****INTERDIT isatty*****/

	if (g_shell_is_interactive)
	{
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp())) /*****INTERDIT tcgetpgrp*****/
			kill(-g_shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		g_shell_pgid = getpid();
		if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		{
			perror("No se pudo poner el shell en su propio grupo de procesos.");
			exit(1);
		}
		tcsetpgrp(g_shell_terminal, g_shell_pgid); /*****INTERDIT tcsetpgrp*****/
		tcgetattr(g_shell_terminal, &g_shell_tmodes); /*****INTERDIT tcgetattr*****/
	}
}

void	launch_process(t_process *process_list, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
	pid_t		pid;

	if (g_shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(g_shell_terminal, pgid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	execvp(process_list->argv[0], process_list->argv);  /*****INTERDIT execvp*****/
	perror("execvp");
	exit(1);
}

void	launch_job(t_job *job_list, int foreground)
{
	t_process	*process_list;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	infile = job_list->stdin;
	process_list = job_list->first_process;
	while (process_list)
	{
		if (process_list->next)
		{
			if (pipe(mypipe) < 0)
			{
				perror("pipe");
				exit(1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = job_list->stdout;
		pid = fork();
		if (pid == 0)
			launch_process(process_list, job_list->pgid, infile, outfile, job_list->stderr, foreground);
		else if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else
		{
			process_list->pid = pid;
			if (g_shell_is_interactive)
			{
				if (job_list->pgid)
					job->pgid = pid;
				setpgid(pid, job_list->pgid);
			}
		}
		if (infile != j->stdin)
			close(infile);
		if (outfile != job_list->stdout)
			close(outfile);
		infile = mypipe[0];
		process_list = process_list->next;
	}
	format_job_info(job_list, "launched");
	if (!g_shell_is_interactive)
		wait_for_job(job_list);
	else if (foreground)
		put_job_in_foreground(job_list, 0);
	else
		put_job_in_background(job_list, 0);
}
