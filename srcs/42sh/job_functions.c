/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/15 10:18:42 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		mark_job_as_running(t_jobs *job)
{
	t_cmd	*cmd;

	cmd = job->t_cmd;
	while (cmd)
	{
		cmd->stopped = 0;
		cmd = cmd->next;
	}
	job->notified = 0;
}

void		continue_job(t_jobs *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}

void		fg_builtin(void)
{
	t_jobs	*tmp;

	tmp = g_tracking.jobs;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		continue_job(tmp, 1);
	}
	else
		ft_putendl("No jobs 😂");
}

void		bg_builtin(void)
{
	t_jobs	*tmp;

	tmp = g_tracking.jobs;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		continue_job(tmp, 0);
	}
	else
		ft_putendl("No jobs 😂");
}

void		jobs_builtin(void)
{
	t_jobs	*tmp;

	tmp = g_tracking.jobs;
	if (tmp)
	{
		while (tmp)
		{
			ft_putchar('[');
			ft_putnbr(tmp->place);
			ft_putchar(']');
			if (tmp->next)
			{
				if (!tmp->next->next)
					ft_putchar('-');
				else
					ft_putchar(' ');
			}
			else if (!tmp->next)
				ft_putchar('+');
			ft_putstr("  ");
			if (tmp->t_cmd->stopped == 1)
				ft_putstr("Stopped");
			else
				ft_putstr("       ");
			ft_putstr("           ");
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	else
		ft_putendl("No jobs bro");
}

void		jobs_notifications(void)
{
	t_jobs	*job;
	t_jobs	*joblast;
	t_jobs	*jobnext;
	t_cmd	*cmd;

	update_status();
	joblast = NULL;
	job = g_tracking.jobs;
	while (job)
	{
		if (job->backstart == 1)
		{
			job->backstart = 0;
			ft_putchar('[');
			ft_putnbr(job->place);
			ft_putchar(']');
			ft_putchar(' ');
			ft_putnbr(job->jpid);
			ft_putchar('\n');
		}
		jobnext = job->next;
		if (job_is_done(job))
		{
			if (job->background == 1)
			{
				cmd = job->t_cmd;
				while (cmd)
				{
					// ft_putendl("AA");
					if (!WIFSIGNALED(cmd->status))
					{
						show_job_info(job, "Done           ", 1);
						break ;
					}
					cmd = cmd->next;
					if (!cmd)
					{
						show_job_info(job, "Killed ", 3);
					}
				}
			}
			if (joblast)
				joblast->next = jobnext;
			else
				g_tracking.jobs = jobnext;
			free_job(job);
		}
		else if (job_is_stopped(job) && !job->notified)
		{
			show_job_info(job, "Stopped                ", 2);
			job->notified = 1;
			joblast = job;
		}
		else
			joblast = job;
		job = jobnext;
	}
}

void		show_job_info(t_jobs *job, const char *status, int mode)
{
	if (mode)
	{
		if (mode == 2 || mode == 3)
		ft_putchar('\n');
		ft_putchar('[');
		ft_putnbr(job->place);
		ft_putchar(']');
		if (job->next)
			{
				if (!job->next->next)
					ft_putchar('-');
				else
					ft_putchar(' ');
			}
			else if (!job->next)
				ft_putchar('+');
			ft_putstr("  ");
	}
	else
	{
		ft_putnbr(job->jpid);
		ft_putstr("   ");
	}
	ft_putstr(status);
	if (mode == 3)
	{
		ft_putstr("by signal: ");
		ft_putnbr(WTERMSIG(job->t_cmd->status));
	}
	ft_putchar(' ');
	ft_putendl(job->name);
}

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!update_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

int			update_process_status(pid_t pid, int status)
{
	t_jobs	*job;
	t_cmd	*cmd;

	if (pid > 0)
    {
		job = g_tracking.jobs;
		if (job)
		{
			while (job)
			{
				cmd = job->t_cmd;
				while (cmd)
				{
					if (cmd->cpid == pid)
					{
						cmd->status = status;
						if (WIFSTOPPED(status))
							cmd->stopped = 1;
						else
						{
							cmd->done = 1;
							// if (WIFSIGNALED(status))
       		             	// 	fprintf (stderr, "%d: Terminated by signal %d.\n", (int) pid, WTERMSIG (cmd->status));
						}
					}
					cmd = cmd->next;
				}
				job = job->next;
			}
			return (0);
		}
		else
		{
			fprintf (stderr, "No child process %d.\n", pid);
			return (-1);
		}
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else 
	{
		perror ("waitpid");
		return (-1);
	}
}

void		wait_for_job(t_jobs *job)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!update_process_status(pid, status) && !job_is_stopped(job) &&
	!job_is_done(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	g_tracking.lastreturn = WEXITSTATUS(status);
}

void				put_job_in_foreground(t_jobs *job, int cont)
{
	tcsetpgrp(g_tracking.sterminal, job->jpid);
	if (cont)
	{
		tcsetattr(g_tracking.sterminal, TCSADRAIN, &job->jterm);
		if (kill (- job->jpid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	wait_for_job(job);
	// g_tracking.lastreturn = WEXITSTATUS(status);
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
	tcgetattr(g_tracking.sterminal, &job->jterm);
	// tcsetattr(g_tracking.sterminal, TCSADRAIN, &g_tracking.myterm);
}

void				put_job_in_background(t_jobs *job, int cont)
{
	if (cont)
		if (kill (-job->jpid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
}

void				interactive_check_set_shell_group(void)
{
	g_tracking.sterminal = STDIN_FILENO;
	g_tracking.interactive = isatty(g_tracking.sterminal);
	if (g_tracking.interactive)
	{
	while (tcgetpgrp(g_tracking.sterminal) != (g_tracking.spid = getpgrp()))
		kill(- g_tracking.spid, SIGTTIN);
	}
	g_tracking.spid = getpid();
	if (setpgid(g_tracking.spid, g_tracking.spid) < 0)
	{
    	perror("Couldn't put the shell in its own process group");
		exit(1);
	}
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
}

int					job_is_done(t_jobs *job)
{
  struct s_cmd		*p;

	p = job->t_cmd;
	while (p)
	{
		if (p->done == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int					job_is_stopped(t_jobs *job)
{
  struct s_cmd		*p;

	p = job->t_cmd;
	while (p)
	{
		if (p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

t_jobs				*find_job (pid_t jpid)
{
  struct s_jobs		*j;

	j = g_tracking.jobs;
	while (j && j->jpid != jpid)
	{
		if (j->jpid == jpid)
			return (j);
	}
	return (NULL);
}