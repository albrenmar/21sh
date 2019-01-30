/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:06:00 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/26 06:32:29 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"
# define LEER		0
# define ESCRIBIR	1

void	execute_end_cmd(t_ast *ast_cmd, int *descrf_two, char **tablist)
{
	pid_t	pid1;
	char	**tab_cmd;

	if (ast_cmd && (ast_cmd->next_token == 0))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf_two[LEER], 0);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		close(descrf_two[0]);
		close(descrf_two[1]);
		wait(&pid1);
	}
}

void	execute_pipe_two(t_ast *ast_cmd, int *descrf, char **tablist)
{
	pid_t	pid1;
	int		descrf_two[2];
	char	**tab_cmd;

	pipe(descrf_two);
	if (ast_cmd && (ast_cmd->next_token == 1))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[LEER], 0);
			dup2(descrf_two[ESCRIBIR], 1);
			close(descrf_two[LEER]);
			close(descrf[ESCRIBIR]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
	}
	descrf[LEER] = descrf_two[LEER];
	close(descrf_two[ESCRIBIR]);
}

void	execute_first_pipe(t_ast *ast_cmd, char **tablist)
{
	pid_t	pid1;
	char	**tab_cmd;
	int		descrf[2];

	tab_cmd = cmd_to_tab(ast_cmd, tablist);
	pipe(descrf);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(descrf[ESCRIBIR], 1);
		close(descrf[LEER]);
		execve(tab_cmd[0], tab_cmd, NULL);
		perror(tab_cmd[0]);
	}
	wait(&pid1);
	ast_cmd = ast_cmd->next;
	close(descrf[ESCRIBIR]);
	while (ast_cmd->next && ast_cmd->next_token == 1)
	{
		execute_pipe_two(ast_cmd, descrf, tablist);
		ast_cmd = ast_cmd->next;
	}
	if (ast_cmd ->next_token == 0)
		execute_end_cmd(ast_cmd, descrf, tablist);
}
