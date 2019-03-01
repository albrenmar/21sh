/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/01 07:40:54 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	print_last(t_last *list)
{
	while (list)
	{
		printf("CMD = %s TYPE = %d\n", list->name, list->type);
		list = list->next;
	}
}

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
	if (!list_cmd)
		return (0);
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
			if (ft_strlen(tree->cmd) == 1 && tree->cmd[0] == '&')
				foreground = 1;
			ret = exec_command(tree->left->list_cmd, foreground, job);
			foreground = 0;
		}
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left, job);
		if (ft_strlen(tree->cmd) > 1)
		{
			if (tree->cmd[0] == '&' && g_tracking.lastreturn == 1)
				return ;
			if (tree->cmd[0] == '|' && g_tracking.lastreturn == 0)
				return ;
			//printf("RETOUR NEXT = %d\n", g_tracking.lastreturn);
		//	printf("EN FONCTION DE [%s]\n", tree->cmd);
		}
		if (tree->right && tree->right->type != SEP)
		{
			if (tree->prev && ft_strlen(tree->prev->cmd) == 1 && tree->prev->cmd[0] == '&')
				foreground = 1;
			ret = exec_command(tree->right->list_cmd, foreground, job);
			foreground = 0;
		}
		else if (tree->right)
		{
			execute_ast(tree->right, job);
		}
	}
	return ;
}
