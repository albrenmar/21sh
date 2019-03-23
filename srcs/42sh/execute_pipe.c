/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/23 04:41:46 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		execute_two(char **tab_exec)
{
	char	**tab_exec_hold;

	tab_exec_hold = tab_dup(tab_exec);
	if (is_builtin())
		ft_exit(0, builtin_exec(NULL));
	if ((tab_exec = hashed_command(tab_exec, 0)))
	{
		execve(tab_exec[0], tab_exec, init_envp(g_tracking.mysh->env));
		free_tab(tab_exec_hold);
		ft_exit(0, EXIT_FAILURE);
	}
	else if ((test_exist_fonction(tab_exec_hold, 2)))
	{
		execve(tab_exec_hold[0], tab_exec_hold, init_envp(g_tracking.mysh->env));
		exec_errors(tab_exec, 0);
		free_tab(tab_exec_hold);
		ft_exit(0, EXIT_FAILURE);
	}
	else
	{
		exec_errors(NULL, 1);
		free_tab(tab_exec_hold);
		ft_exit(0, EXIT_FAILURE);
	}
}

void		execute_pipe_two(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;

	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			set_jobs(job, pid0);
			set_fd_before_exec();
			close_and_dup(2);
			execute_two(tab_exec);
		}
		else
			set_new_process(job, pid0);
	}
	else
		g_tracking.builtin = 1;
}

void		execute_pipe(char **tab_exec, t_jobs *job)
{
	pid_t	pid0;

	swap_descrf();
	pipe(descrf_two);
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			set_jobs(job, pid0);
			set_fd_before_exec();
			close_and_dup(1);
			execute_two(tab_exec);
		}
		else
		{
			close(descrf_two[1]);
			set_new_process(job, pid0);
		}
	}
	else
		g_tracking.builtin = 1;
}
