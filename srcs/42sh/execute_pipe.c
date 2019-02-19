/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/19 02:04:54 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

//#define ORDER g_tracking.mysh->order
//#define EXEC g_tracking.mysh->exec

/*void		execute_two(void)
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
*/
/*void		execute_pipe_two(int fd)
{
	int		status;
	int		j;
	pid_t	pid0;
	pid0 = fork();
	if (pid0 == 0)
	{
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		if ((EXEC->left->tab_test = test_exist_fonction(EXEC->left->tab_test)))
		{
			execve(EXEC->left->tab_test[0], EXEC->left->tab_test, NULL);
			perror("FAIL");
		}
		else
			exit(-1);
	}
	else
	{
		waitpid(pid0, &status, WUNTRACED);
		j = WEXITSTATUS(status);
	}
	if (j != 0)
		EXEC->ret = -1;
	return ;
}

void		execute_pipe(void)
{
	pid_t	pid0;
	int		j;
	int		status;

	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
	pid0 = fork();
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
	return ;
}*/
