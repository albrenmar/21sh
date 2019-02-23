/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/23 12:42:09 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		exec_command(t_last *list_cmd, int foreground, t_jobs *job)
{
	t_last	*temp_command;
	int		redir;
	char	**tab_exec;

	redir = 0;
	tab_exec = NULL;
	temp_command = NULL;
	pipe(descrf);
	pipe(descrf_two);
	job = new_job(list_cmd, foreground);
	g_tracking.mysh->set_fd = ft_memalloc(sizeof(t_set_fd));
	g_tracking.mysh->set_fd->STDIN = 0;
	g_tracking.mysh->set_fd->STDOUT = 1;
	g_tracking.mysh->set_fd->STDERR = 2;
	while (list_cmd)
	{
		if (list_cmd->type == CMD)
		{
			temp_command = list_cmd;
			list_cmd = list_cmd->next;
		}
		else if (list_cmd->type == OP && its_pipe(list_cmd) && temp_command && redir == 0)
		{
			tab_exec = create_tab_to_exec(temp_command);
			execute_pipe(tab_exec, job);
			tab_exec = NULL;
			temp_command = NULL;
			list_cmd = list_cmd->next;
		}
		else if (list_cmd->type == OP && (its_reddir(list_cmd) || its_fd_reddir(list_cmd)))
		{
			redir++;
			create_fich(list_cmd);
			list_cmd = list_cmd->next;
		}
		else if (!temp_command)
			list_cmd = list_cmd->next;
		else if (list_cmd->type == FICH || list_cmd->type == OPT || list_cmd->type == ARG)
			list_cmd = list_cmd->next;
		if (temp_command && (!list_cmd || (its_pipe(list_cmd) && redir != 0)))
		{
			tab_exec = create_tab_to_exec(temp_command);
			execute_pipe_two(tab_exec, job);
			tab_exec = NULL;
			temp_command = NULL;
			redir = 0;
		}
	}
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
		g_tracking.lastreturn = builtin_exec();
	}
	return (0);
}

void		execute_ast(t_tree *tree, t_jobs *job)
{
	int		ret;
	int		foreground;

	ret = 0;
	foreground = 0;
	if (tree->type == SEP)
	{
		if (tree->left && tree->left->type != SEP)
		{
			printf("____________________________________-\n");
			printf("EXECUTE JOBS [1]\n");
			if (ft_strlen(tree->cmd) == 1 && tree->cmd[0] == '&')
			{
				foreground = 1;
				//printf("BACK !!!!!!!!!!!!!!!!!!!\n");
			}
			//print_last(tree->left->list_cmd);
			ret = exec_command(tree->left->list_cmd, foreground, job);
			printf("____________________________________-\n");
		}
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left, job);
		if (ft_strlen(tree->cmd) > 1)
			printf("EN FONCTION DE [%s]\n", tree->cmd);
		if (tree->right && tree->right->type != SEP)
		{
			printf("____________________________________-\n");
			printf("EXECUTE JOBS [2]\n");
			if (tree->prev && ft_strlen(tree->prev->cmd) == 1 && tree->prev->cmd[0] == '&')
			{
				foreground = 1;
				//printf("BACK !!!!!!!!!!!!!!!!!!!\n");
			}
			//print_last(tree->right->list_cmd);
			printf("____________________________________-\n");
			ret = exec_command(tree->right->list_cmd, foreground, job);
		}
		else if (tree->right)
		{
			execute_ast(tree->right, job);
		}
	}
	return ;
}
