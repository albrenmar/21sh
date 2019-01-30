/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:40:13 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/26 06:32:23 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"
# define LEER		0
# define ESCRIBIR	1

/*
void	execute_first_redir(t_ast *ast_cmd, char **tablist)
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
}*/
