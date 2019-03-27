/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/27 04:43:00 by alsomvil         ###   ########.fr       */
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
		execve(tab_exec_hold[0], tab_exec_hold,
				init_envp(g_tracking.mysh->env));
		exec_errors(tab_exec, 0);
		free_tab(tab_exec_hold);
		ft_exit(0, EXIT_FAILURE);
	}
	exec_errors(NULL, 1);
	free_tab(tab_exec_hold);
	ft_exit(0, EXIT_FAILURE);
}

void		close_fd(void)
{
	if (g_tracking.mysh->set_fd->STDIN != 0
			&& g_tracking.mysh->set_fd->STDIN > 2)
		close(g_tracking.mysh->set_fd->STDIN);
	if (g_tracking.mysh->set_fd->STDOUT != 1
			&& g_tracking.mysh->set_fd->STDOUT > 2)
		close(g_tracking.mysh->set_fd->STDOUT);
	if (g_tracking.mysh->set_fd->STDERR != 2
			&& g_tracking.mysh->set_fd->STDERR > 2)
		close(g_tracking.mysh->set_fd->STDERR);
}

void		execute_pipe_two(char **tab_exec, t_jobs *job, int readpipe)
{
	pid_t	pid0;

	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	dprintf(2, "TEST= %d\n", g_tracking.mysh->errchk);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			set_jobs(job, pid0);
			dup2(readpipe, 0);
			if (readpipe > 2)
				close(readpipe);
			set_fd_before_exec();
			execute_two(tab_exec);
		}
		else
		{
			if (readpipe > 2)
				close(readpipe);
			set_new_process(job, pid0);
			g_tracking.mysh->errchk = 0;
			close_fd();
		}
	}
	else
	{
		free_tab(tab_exec);
		g_tracking.builtin = 1;
	}
}

int			execute_pipe(t_last **list_cmd, t_jobs *job, int readpipe)
{
	pid_t	pid0;
	char	**tab_exec;
	int		descrf[2];

	*list_cmd = (*list_cmd)->next;
	pipe(descrf);
	tab_exec = create_tab_to_exec(g_tracking.temp_command);
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	dprintf(2, "TESTIIIIIIIIII= %d\n", g_tracking.mysh->errchk);
	if (!is_builtin_alone())
	{
		if (!is_builtin())
			hash_binary();
		pid0 = fork();
		if (pid0 == 0)
		{
			dup2(readpipe, 0);
			if (readpipe > 2)
				close(readpipe);
			close(descrf[0]);
			dup2(descrf[1], 1);
			close(descrf[1]);
			set_jobs(job, pid0);
			set_fd_before_exec();
			execute_two(tab_exec);
		}
		else
		{
			close(descrf[1]);
			if (readpipe > 2)
				close(readpipe);
			set_new_process(job, pid0);
			return (descrf[0]);
		}
	}
	free_tab(tab_exec);
	g_tracking.builtin = 1;
	return (0);
}
