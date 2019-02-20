/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 11:48:44 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int		exec_command(t_last *list_cmd)
{
	pipe(descrf);
	pipe(descrf_two);
	t_last	*temp_command;
	int		redir;
	char	**tab_exec;
	int		STDIN;
	int		STDOUT;
	int		STDERR;

	redir = 0;
	tab_exec = NULL;
	temp_command = NULL;
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
			else if (list_cmd->type == OP && (its_reddir(list_cmd) ||its_fd_reddir(list_cmd)))
			{
				printf("IL FAUT CREER UN FICHIER\n");
				redir++;;
				if (its_reddir(list_cmd))
				{
					//SET FD SI DESCR TANT QUE LIST_CMD OU LIST_CMD != OP
					//STDOUT = CREATION DU PROCHAIN FICH
				}
				else if (its_fd_reddir(list_cmd))
				{
					//SET DU FD AVEC CREATION DU PROCHAIN FICH
					//SET FD SI DESCR TANT QUE LIST_CMD OU LIST_CMD != OP
				}
				list_cmd = list_cmd->next;
			}
			else if (list_cmd->type == DESCR)
			{
				printf("SET DU FD AVEC : %s\n", list_cmd->name);
				//SET DU FD
				list_cmd = list_cmd->next;
			}
			else if (!temp_command)
			{
				printf("J'IGNORE : %s\n", list_cmd->name);
				list_cmd = list_cmd->next;
			}
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
