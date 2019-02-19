/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/19 06:59:09 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int		exec_command(t_last *list_cmd)
{
	pipe(descrf);
	pipe(descrf_two);
	int		close_fd;
	t_last	*temp_list;

	//init_fd(NULL);
	while (list_cmd)
	{
		printf("CMD = %s TYPE = %d\n", list_cmd->name, list_cmd->type);
		list_cmd = list_cmd->next;
	}
	/*while (list_cmd)
	{
		if (list_cmd->type == CMD)
		{
			if (next_is_pipe(list_cmd))
			{
				pipe(descrf_two);
				execute_pipe();
			}
			else if (next_is_reddir(list_cmd))
			{
				if ((temp_list = its_fd_reddir(list_cmd)))
					create_fich(temp_list, list_cmd);
			}
			list_cmd = list_cmd->next;
		}
		if (list_cmd->type == DESCR)
		{
			init_fd(list_cmd);
		}
	}*/
	/*while (ORDER)
	{
		while (ORDER && ORDER->sym && ORDER->sym[0] == '|')
		{
	y1		descrf[0] = descrf_two[0];
			descrf[1] = descrf_two[1];
			pipe(descrf_two);
			execute_pipe();
			ORDER = ORDER->next;
			if (!ORDER->next)
			{
				execute_pipe_two(0);
				ORDER = ORDER->next;
			}
		}
		if (ORDER && ORDER->sym && (ORDER->sym[0] == '>' || ORDER->sym[1] == '>'))
		{
			temp_command = ORDER;
			while (ORDER && ORDER->sym && (ORDER->sym[0] == '>' || ORDER->sym[1] == '>'))
			{
				ORDER = ORDER->next;
				if (ft_strlen(ORDER->sym) == 2)
					close_fd = open(ORDER->command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
				else
					close_fd = open(ORDER->command[0], O_CREAT | O_APPEND | O_RDWR, 0644);
			}
			ORDER = ORDER->next;
			temp_command_next = ORDER;
			ORDER = temp_command;
			execute_pipe_two(close_fd);
			close(close_fd);
			ORDER = temp_command_next;
		}
	}
	if (EXEC->ret == 0)
		EXEC->ret = 1;*/
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
			ret = exec_command(tree->left->list_cmd);
		}
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left);
		printf("SUIVANT LE RETOUR AVANT [%s]\n", tree->cmd);
		if (tree->right && tree->right->type != SEP)
		{
			ret = exec_command(tree->right->list_cmd);
		}
		else if (tree->right)
			execute_ast(tree->right);
	}
	return ;
}
