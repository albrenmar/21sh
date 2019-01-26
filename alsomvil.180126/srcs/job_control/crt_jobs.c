/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:28:28 by mjose             #+#    #+#             */
/*   Updated: 2019/01/26 09:12:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "minishell.h"
#include "job_control.h"

void	crt_job_processes(t_job *jobs)
{
	t_job	*first_job;

	first_job = jobs;
	jobs->ast = NULL;
	while (jobs)
	{
		if (search_symbol(jobs->command))
			create_ast(jobs->command, jobs->ast);
		crt_processes(jobs->first_process, jobs->command, jobs->ast);
		jobs = jobs->next;
	}
	jobs = first_job;
}

t_job	*new_job(void)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	job->command = NULL;
	job->first_process = new_process();
	job->ast = NULL;
	job->next = NULL;
	job->prev = NULL;
	return (job);
}

void	crt_jobs(t_shell *shell, t_last *cmd)
{
	t_job	*job;
	t_job	*begin;
	t_job	*prev;

	job = new_job();
	while (cmd && cmd->name)
	{
		job->command = ft_strtrim(cmd->name);
		if (cmd->next && cmd->next->name)
		{
			job->next = new_job;
			job = job->next;
			job->prev = prev;
			cmd = cmd->next;
			prev = job;
		}
	}
	job->next = NULL;
	crt_job_processes(begin);
	shell->jobs = begin;
}
