/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/22 08:12:03 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		exec_command(t_last *list_cmd)
{
	t_last	*temp_command;
	int		redir;
	char	**tab_exec;

	redir = 0;
	tab_exec = NULL;
	temp_command = NULL;
	pipe(descrf);
	pipe(descrf_two);
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
			execute_pipe(tab_exec);
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
			execute_pipe_two(tab_exec);
			tab_exec = NULL;
			temp_command = NULL;
			redir = 0;
		}
	}
	return (0);
}

void		execute_ast(t_tree *tree)
{
	int		ret;

	ret = 0;
	if (tree->type == SEP)
	{
		if (tree->left && tree->left->type != SEP)
		{
			printf("____________________________________-\n");
			printf("EXECUTE JOBS [1]\n");
			/*if (tree->prev)
			{
				printf("BACKGROUND ???? : %s\n", tree->prev->cmd);
			}*/
			print_last(tree->left->list_cmd);
			//ret = exec_command(tree->left->list_cmd);
			printf("____________________________________-\n");
		}
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left);
		if (ft_strlen(tree->cmd) > 1)
		{
			printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOO-\n");
			printf("EN FONCTION DE [%s]\n", tree->cmd);
			printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOO-\n");
		}
		if (tree->right && tree->right->type != SEP)
		{
			printf("____________________________________-\n");
			printf("EXECUTE JOBS [2]\n");
			if (tree->prev)
			{
				printf("BACKGROUND ???? : %s\n", tree->prev->cmd);
			}
			print_last(tree->right->list_cmd);
			printf("____________________________________-\n");
			//ret = exec_command(tree->right->list_cmd);
		}
		else if (tree->right)
		{
			execute_ast(tree->right);
		}
	}
	return ;
}
