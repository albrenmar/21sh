/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_jobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 23:37:01 by mjose             #+#    #+#             */
/*   Updated: 2019/01/24 05:10:14 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "minishell.h"
#include "job_control.h"

t_process	*new_process(t_process *process)
{
	process = ft_memalloc(sizeof(t_process));
	process->argv = NULL;
	process->next = NULL;
	return (process);
}

t_job		*new_job(t_job *job)
{
	job = ft_memalloc(sizeof(t_job));
	job->command = NULL;
	job->first_process = ft_memalloc(sizeof(t_process));
	job->first_process->next = NULL;
	job->next = NULL;
	return (job);
}

t_process	*create_process(char *full_cmd, t_process *process)
{

		while (temp_ast && temp_ast->next)
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
	else
		temp_proc->argv = ft_strsplit(full_cmd, ' ');
	return (process);
}

void		create_job(char *full_cmd, t_job *job)
{
	t_ast		*ast_cmd;
	t_ast		*temp_ast;
	t_process	*temp_proc;

	ast_cmd = NULL;

	job->first_process = NULL;
	job->first_process = new_process(job->first_process);
	temp_proc = process;
	if (search_symbol(full_cmd))
	{
		ast_cmd = new_first_list(ast_cmd, 0);
		create_ast(full_cmd, ast_cmd);
		temp_ast = ast_cmd;
	}
	job->first_process = new_process(job->first_process);
	job->command = ft_strdup(full_cmd);
	
	job->first_process = create_process(full_cmd, job->first_process, ast);
}

void		crt_jobs(t_shell *shell, t_last *cmd)
{
//	t_ast	*ast_cmd;
//	t_ast	*temp_ast;

//	ast_cmd = NULL;
//	ast_cmd = new_first_list(ast_cmd, 0);
	shell->jobs = NULL;
	shell->jobs = new_job(shell->jobs);
//	temp_ast = ast_cmd;
	while (cmd && cmd->next)
	{
		create_job(cmd->name, shell->jobs);
//		if (search_symbol(cmd->name))
//			create_ast(cmd->name, ast_cmd);
	}
}
