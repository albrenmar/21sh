/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 23:37:01 by mjose             #+#    #+#             */
/*   Updated: 2019/01/25 05:39:46 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "minishell.h"
#include "job_control.h"
#include <stdio.h>

int					g_shell_terminal;
int					g_shell_is_interactive = 1;
t_job				*g_first_job = NULL;
pid_t				g_shell_pgid;
struct termios		g_shell_tmodes;

int		mark_process_status(pid_t pid, int status)
{
	t_job		*job_list;
	t_process	*process_list;

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

void	format_job_info(t_job *job_list, const char *status)
{
	fprintf(stderr, "%ld (%s): $s\n", (long)job_list->pgid, status, job_list->command);
}

void	wait_for_job(t_job	*job_list)
{
	int		status;
	pid_t	pid;

	while (mark_process_status(pid, status) && !job_is_stopped(job_list) && job_is_completed(job_list))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void	put_job_in_foreground(t_job *job_list, int cont)
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

void	put_job_in_background(t_job *job_list, int cont)
{
	if (cont)
		if (kill(-job_list->pgid, SIGCONT) < 1)
			perror("kill(SIGCONT)");
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
t_process	*new_process(void)
{
	t_process	*process;

	process = ft_memalloc(sizeof(t_process));
	process->argv = NULL;
	process->next = NULL;
	process->prev = NULL;
	return (process);
}

t_job		*new_job(void)
{
	t_job 	*job;

	job = ft_memalloc(sizeof(t_job));
	job->command = NULL;
	job->first_process = new_process();
	job->first_process->next = NULL;
	job->first_process->prev = NULL;
	job->next = NULL;
	job->prev = NULL;
	return (job);
}

void	crt_processes(t_process *proc_list, t_ast *ast, char *command)
{
	t_process	*first_proc;
	t_process	*prev;

	first_proc = proc_list;
	prev = first_proc;
	if (!search_symbol(command))
	{
		proc_list->argv = ft_strsplit(command, ' ');
	//	proc_list->next = new_process();
	//	proc_list = proc_list->next;
	//	proc_list->prev = prev;
	//	prev = proc_list;
	}
	else
		while (ast && ast->next)
		{
			proc_list->argv = ft_strsplit(ast->cmd, ' ');
			proc_list->next = new_process();
			proc_list = proc_list->next;
			proc_list->prev = prev;
			ast = ast->next;
			prev = proc_list;
		}
	proc_list->next = NULL;
	proc_list = first_proc;
}

void	crt_job_processes(t_job *job_list)
{
	t_ast	*ast_cmd;
	t_ast	*temp_ast;
	t_job	*first_job;

	ast_cmd = NULL;
	ast_cmd = new_first_list(ast_cmd, 0);
	temp_ast = ast_cmd;
	first_job = job_list;
	while (job_list && job_list->next)
	{
		if (search_symbol(job_list->command))
		{
			create_ast(job_list->command, ast_cmd);
			crt_processes(job_list->first_process, ast_cmd, job_list->command);
		}
		else
			crt_processes(job_list->first_process, NULL, job_list->command);
		job_list = job_list->next;
	}
	job_list = first_job;
/*	while (temp_ast && temp_ast->next)
	{
		temp_proc->argv = ft_strsplit(temp_ast->cmd, ' ');
		if (temp_ast->next)
		{
			temp_proc = temp_proc->next;
			temp_ast = temp_ast->next;
		}
		temp_proc = new_process(temp_proc);
	}
	temp_proc = new_process(temp_proc);
	temp_proc->argv = ft_strsplit(temp_ast->cmd, ' ');
	}
	return (process);
*/}
/*
void		create_job(char *full_cmd, t_job *job)
{
	t_ast		*ast_cmd;
	t_ast		*temp_ast;
	t_process	*temp_proc;

	ast_cmd = NULL;
	job->first_process = NULL;
	job->first_process = new_process(job->first_process);
	temp_proc = job->first_process;
	if (search_symbol(full_cmd))
	{
		ast_cmd = new_first_list(ast_cmd, 0);
		create_ast(full_cmd, ast_cmd);
		temp_ast = ast_cmd;
		job->first_process = create_process(full_cmd, job->first_process, ast);
	}
	job->command = ft_strdup(full_cmd);
	else
	{
		temp_proc->argv = ft_strsplit(full_cmd, ' ');
		job->first_process = create_process(full_cmd, job->first_process, ast);
	}
}
*/

void		crt_jobs(t_shell *shell, t_last *cmd)
{
	t_job	*job;
	t_job	*begin;
	t_job	*prev;
	int		i;

	job = new_job();
	begin = job;
	prev = begin;
	while (cmd && cmd->name)
	{
		job->command = ft_strtrim(cmd->name);
		job->next = new_job();
		job = job->next;
		job->prev = prev;
		cmd = cmd->next;
		prev = job;
	}
	job->next = NULL;
	crt_job_processes(begin);
	shell->jobs = begin;
/*	while (shell->jobs->next)
	{
		i = 0;
		printf("job --> %s\n", shell->jobs->command);
		while(shell->jobs->first_process)
		{
			i = 0;
			while(shell->jobs->first_process->argv[i])
				printf("process --> %s\n", shell->jobs->first_process->argv[i++]);
//			if (shell->jobs->first_process->next)	
				shell->jobs->first_process = shell->jobs->first_process->next;
		}
		shell->jobs = shell->jobs->next;
	}
*/	launch_job(shell->jobs, 0);
}
