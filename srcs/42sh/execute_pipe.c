/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 20:00:35 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

//#define ORDER g_tracking.mysh->order
//#define EXEC g_tracking.mysh->exec

void		execute_two(char **tab_exec)
{
	if ((tab_exec = test_exist_fonction(tab_exec)))
	{
		execve(tab_exec[0], tab_exec, NULL);
		perror("FAIL");
	}
	else
	{
		exit(-1);
	}
}


void		execute_pipe_two(char **tab_exec)
{
	int		status;
	int		j;
	pid_t	pid0;

	pid0 = fork();
	if (pid0 == 0)
	{
		if (g_tracking.mysh->set_fd->STDIN != 0)
			dup2(g_tracking.mysh->set_fd->STDIN, 0);
		if (g_tracking.mysh->set_fd->STDOUT != 1)
			dup2(g_tracking.mysh->set_fd->STDOUT, 1);
		if (g_tracking.mysh->set_fd->STDERR != 2)
			dup2(g_tracking.mysh->set_fd->STDERR, 2);
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_two(tab_exec);
	}
	else
	{
		waitpid(pid0, &status, WUNTRACED);
		j = WEXITSTATUS(status);
	}
	/*if (j != 0)
		EXEC->ret = -1;*/
	return ;
}

void		execute_pipe(char **tab_exec)
{
	pid_t	pid0;
	int		j;
	int		status;

	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
	pipe(descrf_two);
	pid0 = fork();
	if (pid0 == 0)
	{
		if (g_tracking.mysh->set_fd->STDIN != 0)
			dup2(g_tracking.mysh->set_fd->STDIN, 0);
		if (g_tracking.mysh->set_fd->STDOUT != 1)
			dup2(g_tracking.mysh->set_fd->STDOUT, 1);
		if (g_tracking.mysh->set_fd->STDERR != 2)
			dup2(g_tracking.mysh->set_fd->STDERR, 2);
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_two(tab_exec);
	}
	else
	{
		close(descrf_two[1]);
		j = WEXITSTATUS(status);
	}
	/*if (j != 0)
		EXEC->ret = -1;*/
	return ;
}
