/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/16 05:13:30 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "sh42.h"
#include <sys/types.h>
#include <sys/wait.h>

#define ORDER g_tracking.mysh->order
#define EXEC g_tracking.mysh->exec

char			**init_envp(t_lstcontainer *env);

void		execute_two(void)
{
	if ((ORDER->command = test_exist_fonction(ORDER->command)))
	{
		execve(ORDER->command[0], ORDER->command, NULL);
		perror("FAIL");
	}
	else
	{
		exit(-1);
	}
}

void		execute_pipe_two(int fd)
{
	int		status;
	int		j;
	pid_t	pid0;
	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		if (fd != 0)
		{
			dup2(fd, 1);
		}
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		if ((ORDER->command = test_exist_fonction(ORDER->command)))
		{
			execve(ORDER->command[0], ORDER->command, g_tracking.mysh->tab_env);
			perror("FAIL");
		}
		else
		{
			exit(-1);
		}
	}
	else
	{
		waitpid(pid0, &status, WUNTRACED);
		j = WEXITSTATUS(status);
	}
	if (j != 0)
		EXEC->ret = -1;
	dprintf(2, "TEST1 =%d\n", EXEC->ret);
	return ;
}

void		execute_pipe(void)
{
	pid_t	pid0;
	int		j;
	int		status;

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
	{
		close(descrf_two[1]);
		j = WEXITSTATUS(status);
	}
	if (j != 0)
		EXEC->ret = -1;
	dprintf(2, "TEST =%d\n", EXEC->ret);
	return ;
}

/*void		test_pipe(void)
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
}*/
