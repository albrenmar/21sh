/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/24 18:42:55 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		jobs_update_currentback(int mode)
{
	t_jobs	*tmp;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	if (!tmp->next)
	{
		tmp->current = 1;
		tmp->currentback = 0;
		return ;
	}
	else if (mode == 1)
	{
		while (tmp->next)
		{
			tmp->current = 0;
			tmp->currentback = 0;
			tmp = tmp->next;
		}
		while (tmp->prev && tmp->t_cmd->stopped != 1)
			tmp = tmp->prev;
		tmp->current = 1;
		tmp->currentback = 0;
		if (tmp->next)
		{
			hold = tmp->next;
			while (hold->next)
				hold = hold->next;
		}
		else
			hold = tmp->prev;
	}
	else if (mode > 1)
	{
		while (tmp->next)
		{
			tmp->current = 0;
			tmp->currentback = 0;
			tmp = tmp->next;
		}
		tmp->current = 0;
		tmp->currentback = 0;
		while (tmp)
		{
			if (tmp->t_cmd->stopped == 1)
			{
				if (hold == NULL)
				{
					tmp->current = 1;
					tmp->currentback = 0;
					hold = tmp->prev;
				}
				else
				{
					tmp->current = 0;
					tmp->currentback = 1;
					return ;
				}
			}
			if (!tmp->prev)
				break ;
			tmp = tmp->prev;
		}
	}
	hold->current = 0;
	hold->currentback = 1;
}

void		jobs_update_current(void)
{
	t_jobs	*tmp;
	int		mode;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	mode = suspended_jobs_count();
	if (tmp)
	{
		if (mode == 0)
		{
			while (tmp->next)
			{
				tmp->current = 0;
				tmp->currentback = 0;
				hold = tmp;
				tmp = tmp->next;
			}
			tmp->currentback = 0;
			if (hold != NULL)
				hold->currentback = 1;
			tmp->current = 1;
		}
		else
			jobs_update_currentback(mode);
	}
}

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

int			fg_builtin_output(t_jobs *tmp)
{
	ft_putendl(tmp->name);
	tmp->background = 0;
	continue_job(tmp, 1);
	return (0);
}

int			fg_builtin(void)
{
	t_jobs	*tmp;
	char	*hold;
	int		nb;

	nb = 0;
	tmp = g_tracking.jobs;
	if (tmp->next)
	{
		if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] == '%')
		{
			hold = parse_job_number(g_tracking.g_tab_exec[1]);
			if (hold)
				nb = ft_atoi(hold);
			if (job_exists(parse_job_sign(g_tracking.g_tab_exec[1])))
			{
				while (tmp->prev)
					tmp = tmp->prev;
				nb = parse_job_sign(g_tracking.g_tab_exec[1]);
				while (tmp->next && tmp->place != nb)
					tmp = tmp->next;
				if (nb == 0)
					return (errors_fg(0, 2));
				else if (nb != 0)
					return (fg_builtin_output(tmp));
			}
			else if (hold && job_exists(ft_atoi(hold)))
			{
				while (tmp->prev)
					tmp = tmp->prev;
				while (tmp->next && tmp->place != nb)
					tmp = tmp->next;
				return (fg_builtin_output(tmp));
			}
			else if (hold)
				return (errors_fg(ft_atoi(hold), 3));
			else
				errors_fg(0, 2);
		}
		else if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] != '%')
			return (errors_fg(tmp->place, 2));
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp->next && tmp->current != 1)
			tmp = tmp->next;
		return (fg_builtin_output(tmp));
	}
	ft_putendl("No jobs 😂");
	return (1);
}

int			bg_builtin_output(t_jobs *tmp)
{
	if (tmp->background != 1)
	{
		ft_putchar('[');
		ft_putnbr(tmp->place);
		ft_putchar(']');
		ft_putchar('+');
		ft_putchar(' ');
		ft_putstr(tmp->name);
		ft_putchar(' ');
		ft_putchar('&');
		ft_putchar('\n');
		continue_job(tmp, 0);
		tmp->background = 1;
	}
	else
		return (errors_bg(tmp->place, 0));
	return (0);
}

int			bg_builtin(void)
{
	t_jobs	*tmp;
	char	*hold;
	int		nb;

	nb = 0;
	tmp = g_tracking.jobs;
	if (tmp->next)
	{
		if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] == '%')
		{
			hold = parse_job_number(g_tracking.g_tab_exec[1]);
			if (hold)
				nb = ft_atoi(hold);
			if (job_exists(parse_job_sign(g_tracking.g_tab_exec[1])))
			{
				while (tmp->prev)
					tmp = tmp->prev;
				nb = parse_job_sign(g_tracking.g_tab_exec[1]);
				while (tmp->next && tmp->place != nb)
					tmp = tmp->next;
				if (nb == 0)
					return (errors_bg(0, 2));
				else if (nb != 0)
					return (bg_builtin_output(tmp));
			}
			else if (hold && job_exists(ft_atoi(hold)))
			{
				while (tmp->prev)
					tmp = tmp->prev;
				while (tmp->next && tmp->place != nb)
					tmp = tmp->next;
				return (bg_builtin_output(tmp));
			}
			else if (hold)
				return (errors_bg(ft_atoi(hold), 3));
			else
				errors_bg(0, 2);
		}
		else if (g_tracking.g_tab_exec[1] && g_tracking.g_tab_exec[1][0] != '%')
			return (errors_bg(tmp->place, 2));
		while (tmp->prev)
			tmp = tmp->prev;
		while (tmp->next && tmp->current != 1)
			tmp = tmp->next;
		return (bg_builtin_output(tmp));
	}
	ft_putendl("No jobs 😂");
	return (1);
}

int			jobs_builtin_parser(t_jobs *tmp, int optionl, int optionp, char *hold)
{
	int		i;
	int		j;
	int		place;
	int		mode;
	i = 1;
	mode = 0;
	place = 0;
	if (g_tracking.g_tab_exec[1])
	{
		while (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '-')
		{
			if (!g_tracking.g_tab_exec[i][1])
				return (errors_jobs('a', 0, 0));
			j = 1;
			while (g_tracking.g_tab_exec[i][j] != '\0')
			{
				if (g_tracking.g_tab_exec[i][j] != 'l' && g_tracking.g_tab_exec[i][j] != 'p')
					return (errors_jobs(g_tracking.g_tab_exec[i][j], 0, 1));
				else if (g_tracking.g_tab_exec[i][j] == 'l')
					optionl = 1;
				else if (g_tracking.g_tab_exec[i][j] == 'p')
					optionp = 1;
				j++;
			}
			i++;
		}
		if (optionp)
			j = 2;
		else if (optionl)
			j = 1;
		if (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '%')
		{
			while (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '%')
			{
				hold = parse_job_number(g_tracking.g_tab_exec[i]);
				if (job_exists(parse_job_sign(g_tracking.g_tab_exec[i])))
					jobs_builtin_output(tmp, 1, parse_job_sign(g_tracking.g_tab_exec[i]), j);
				else if (hold && job_exists(ft_atoi(hold)))
					jobs_builtin_output(tmp, 1, ft_atoi(hold), j);
				else if (hold)
					errors_jobs('a', ft_atoi(hold), 2);
				else
					errors_jobs('a', 0, 2);
				i++;
			}
			return (0);
		}
		else
		{
			jobs_builtin_output(tmp, 0, 0, j);
			return (0);
		}
	}
	jobs_builtin_output(tmp, 0, 0, 0);
	return (0);
}

void		jobs_builtin_output(t_jobs *tmp, int mode, int number, int options)
{
	while (tmp && tmp->next)
	{
		if (mode == 0 || (mode == 1 && number == tmp->place))
		{
			if (options != 2)
			{
				ft_putchar('[');
				ft_putnbr(tmp->place);
				ft_putchar(']');
				if (tmp->current == 1)
					ft_putchar('+');
				else if (tmp->currentback == 1)
					ft_putchar('-');
				else
					ft_putchar(' ');
				ft_putchar(' ');
			}
			if (options == 1 || options == 2)
				ft_putnbr(tmp->jpid);
			ft_putchar(' ');
			if (options == 2)
				ft_putchar('\n');
			if (options != 2)
			{
				if (tmp->background == 1)
					ft_putstr("Running");
				if (options != 1 && tmp->t_cmd->stopped == 1)
					ft_putstr("Stopped");
				else if (options == 1)
					ft_putstr("Suspended");
				else
					ft_putstr("       ");
				ft_putstr("           ");
				ft_putstr(tmp->name);
				ft_putchar(' ');
				if (tmp->background == 1)
					ft_putchar('&');
				ft_putstr("      ");
				if (ft_strcmp(tmp->wd, getcwd(NULL, 42)))
				{
					ft_putstr("(wd: ");
					ft_putstr(tmp->wd);
					ft_putendl(")  ");
				}
				else
					ft_putchar('\n');
				if (mode == 1 && tmp->place == number)
					return ;
			}
		}
		tmp = tmp->next;
	}
}

int			jobs_builtin(void)
{
	t_jobs	*tmp;
	int		optionl;
	int		optionp;
	char	*place;

	optionl = 0;
	optionp = 0;
	place = NULL;
	tmp = g_tracking.jobs;
	if (tmp && tmp->next)
		return (jobs_builtin_parser(tmp, optionl, optionp, place));
	ft_putendl("No jobs bro");
	return (1);
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
			if (job->current == 1)
				ft_putchar('+');
			else if (job->currentback == 1)
				ft_putchar('-');
			else
				ft_putchar(' ');
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
		if (mode == 2)
			ft_putchar('+');
		else
		{
			if (job->current == 1)
				ft_putchar('+');
			else if (job->currentback == 1)
				ft_putchar('-');
			else
				ft_putchar(' ');
		}
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
		// tcsetattr(g_tracking.sterminal, TCSADRAIN, &job->jterm);
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
/*
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
}*/
