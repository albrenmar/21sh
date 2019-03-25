/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:40:13 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/25 03:46:03 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	wait_job(int foreground, t_last *list_cmd, t_jobs *job)
{
	if (g_tracking.builtin == 0)
	{
		if (!g_tracking.interactive)
			wait_for_job(job);
		else if (!foreground)
			put_job_in_foreground(job, 0);
		else
			put_job_in_background(job, 0);
	}
	else
	{
		g_tracking.builtin = 0;
		g_tracking.lastreturn = builtin_exec(list_cmd);
	}
}

int		init_exec(t_last **list_cmd, t_jobs *job, int readpipe)
{
	int		test;

	test = 0;
	if ((*list_cmd)->type == CMD)
	{
		g_tracking.temp_command = *list_cmd;
		*list_cmd = (*list_cmd)->next;
	}
	else if ((*list_cmd)->type == OP && its_pipe(*list_cmd)
			&& g_tracking.temp_command)
		return (execute_pipe(list_cmd, job, readpipe));
	else if ((*list_cmd)->type == OP && (its_reddir(*list_cmd)
				|| its_fd_reddir(*list_cmd) || its_indir(*list_cmd)))
	{
		if (exec_create_file(list_cmd) == -1)
		{
			if (readpipe > 2)
				close(readpipe);
			return (-1);
		}
	}
	else if (!g_tracking.temp_command || (*list_cmd)->type == FICH
			|| (*list_cmd)->type == OPT || (*list_cmd)->type == ARG)
		*list_cmd = (*list_cmd)->next;
	return (readpipe);
}

int		exec_command(t_last *list_cmd, int foreground, t_jobs *job)
{
	char	**tab_exec;
	int		readpipe;

	readpipe = 0;
	tab_exec = NULL;
	g_tracking.temp_command = NULL;
	if (!list_cmd)
		return (0);
	job = new_job(list_cmd, foreground);
	set_fd_and_descr();
	while (list_cmd)
	{
		if ((readpipe = init_exec(&list_cmd, job, readpipe)) == -1)
			return (-1);
		if (g_tracking.temp_command && !list_cmd)
		{
			tab_exec = create_tab_to_exec(g_tracking.temp_command);
			execute_pipe_two(tab_exec, job, readpipe);
			tab_exec = NULL;
			g_tracking.temp_command = NULL;
			g_tracking.redir = 0;
		}
	}
	wait_job(foreground, list_cmd, job);
	return (0);
}
