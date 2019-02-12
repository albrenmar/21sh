/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/12 04:18:25 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define ORDER g_tracking.mysh->order

void		execute_two(void)
{
	if ((ORDER->command = test_exist_fonction(ORDER->command)))
		execve(ORDER->command[0], ORDER->command, NULL);
	else
	{
		exit(-1);
	}
}

void		execute_pipe_two(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_two();
	}
	else
		close(descrf_two[0]);
}

void		execute_pipe(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_two();
	}
	else
		close(descrf_two[1]);
}

void		test_pipe(void)
{
	if (g_tracking.mysh->exec->sym && ft_strlen(g_tracking.mysh->exec->sym[0]) != 2)
	{
		descrf[0] = descrf_two[0];
		descrf[1] = descrf_two[1];
		pipe(descrf_two);
		execute_pipe();
	}
	else
	{
		execute_pipe_two();
		close(descrf[0]);
		close(descrf[1]);
		close(descrf_two[0]);
		close(descrf_two[1]);
	}
}
