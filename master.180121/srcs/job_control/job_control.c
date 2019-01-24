/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 00:56:21 by mjose             #+#    #+#             */
/*   Updated: 2019/01/23 02:39:13 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_last				*g_first_job = NULL;
pid_t				g_shell_pgid;
struct termios		g_shell_tmodes;
int					g_shell_terminal;
int					g_shell_is_interactive;


t_last	*find_job(pid_t pgid)
{
	t_last	*job_list;

	job_list = g_first_job;
	while (job_list)
	{
		if (job_list->pgid == pgid)
			return (job_list);
		job_list = job_list->next;
	}
	return (NULL);
}

int		job_is_stopped(t_last *job_list)
{
	t_ast	*process_list;

	process_list = job_list->first_process;
	while (process_list)
	{
		if (!process_list->completed && !process_list->stopped)
			return (0);
		process_list = process_list->next;
	}
	return (1);
}

int		job_is_completed(t_last *job_list)
{
	t_ast	*process_list;

	process_list = job_list->first_process;
	while (process_list)
	{
		if (!process_list->completed)
			return (0);
		process_list = process_list->next;
	}
	return (1);
}

void	init_shell_for_job(void)
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

void	launch_process(t_ast *process_list, pid_t pgid, int infile, int outfile, int errfile, int foreground)
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

void	launch_job(t_last *job_list, int foreground)
{
	t_ast	*process_list;
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
					job_list->pgid = pid;
				setpgid(pid, job_list->pgid);
			}
		}
		if (infile != job_list->stdin)
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

void	put_job_in_foreground(t_last *job_list, int cont)
{
	tcsetpgrp(g_shell_terminal, job_list->pgid);
	if (cont)
	{
		tcsetattr(g_shell_terminal, TCSADRAIN, &job_list->tmodes);
		if (kill(-job_list->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	wait_for_job(job_list);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, &job_list->tmodes);
	tcsetattr(g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
}

void	put_job_in_background(t_last *job_list, int cont)
{
	if (cont)
		if (kill(-job_list->pgid, SIGCONT) < 1)
			perror("kill(SIGCONT)");
}

int		mark_process_status(pid_t pid, int status)
{
	t_last		*job_list;
	t_ast	*process_list;

	if (pid > 0)
	{
		job_list = g_first_job;
		while (job_list)
		{
			process_list = job_list->first_process;
			while (process_list)
			{
				if (process_list->pid == pid)
				{
					process_list->status = status;
					if (WIFSTOPPED(status))
						process_list->stopped = 1;
					else
					{
						process_list->completed = 1;
						if (WIFSIGNALED(status))
							fprintf(stderr, "%d: Terminated by signal %d.\n",
								(int)pid, WTERMSIG(process_list->status));
					}
					return (0);
				}
				process_list = process_list->next;
			}
			job_list = job_list->next;
		}
		fprintf(stderr, "No child process %d.\n", pid);
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else
	{
		perror("waitpid");
		return (-1);
	}
}

void	update_status(void)
{
	int		status;
	pid_t	pid;

	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

void	wait_for_job(t_last	*job_list)
{
	int		status;
	pid_t	pid;

	while (mark_process_status(pid, status) && !job_is_stopped(job_list) && job_is_completed(job_list))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void	format_job_info(t_last *job_list, const char *status)
{
	fprintf(stderr, "%ld (%s): $s\n", (long)job_list->pgid, status, job_list->name);
}

void	do_job_notification(void)
{
	t_last		*job;
	t_last		*job_last;
	t_last		*job_next;
	t_ast	*process;

	update_status();
	job_last = NULL;
	job = g_first_job;
	while (job)
	{
		job_next = job->next;
		if (job_is_completed(job))
		{
			format_job_info(job, "completed");
			if (job_last)
				job_last = job_next;
			else
				g_first_job = job_next;
//			free_job(job);
		}
		else if (job_is_stopped(job) && !job->notified)
		{
			format_job_info(job, "stopped");
			job->notified = 1;
			job_last = job;
		}
		else
			job_last = job;
		job = job_next;
	}
}

void	mark_job_as_running(t_last *job_list)
{
	t_ast	*process_list;

	process_list = job_list->first_process;
	while (process_list)
	{
		process_list->stopped = 0;
		process_list = process_list->next;
	}
	job_list->notified = 0;
}

void	continue_job(t_last *job_list, int foreground)
{
	mark_job_as_running(job_list);
	if (foreground)
		put_job_in_foreground(job_list, 1);
	else
		put_job_in_background(job_list, 1);
}
