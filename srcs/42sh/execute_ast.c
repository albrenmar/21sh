/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/18 01:34:12 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

//#define ORDER g_tracking.mysh->order
//#define EXEC g_tracking.mysh->exec

/*void		execute(void)
  {
  if (EXEC->sym[0][0] == '|')
  test_pipe();
  else if (EXEC->sym[0][0] == '>')
  test_redir();
  }*/

/*t_order		*new_order(void)
{
	t_order		*order;

	order = ft_memalloc(sizeof(t_order));
	order->command = NULL;
	order->next = NULL;
	order->prev = NULL;
	order->temp_command = NULL;
	order->temp_command_next = NULL;
	return (order);
}*/

char		**copy_tab(char **copy)
{
	int		i;
	int		j;
	char	**tabcpy;

	i = 0;
	j = 0;
	while (copy[i])
		i++;
	tabcpy = ft_memalloc(sizeof(char *) * (i + 1));
	tabcpy[i] = NULL;
	i = 0;
	while (copy[i])
	{
		tabcpy[i] = ft_strdup(copy[i]);
		i++;
	}
	tabcpy[i] = NULL;
	return (tabcpy);
}

/*void		add_to_exec(int mode)
{
	if (ORDER)
	{
		while (ORDER->next)
		{
			ORDER = ORDER->next;
		}
		ORDER->next = new_order();
		ORDER->next->prev = ORDER;
		ORDER = ORDER->next;
	}
	else
		ORDER = new_order();
	dprintf(2, "TEST = %s\n", EXEC->left->tab_test[0]);
	if (EXEC->left->next)
		dprintf(2, "TEST1 = %s\n", EXEC->left->next->tab_test[0]);
	ORDER->command = copy_tab(EXEC->left->tab_test);
	printf("CMD = %s\n", ORDER->command[0]);
	printf("CMD = %s\n", ORDER->command[1]);
	if (EXEC->sym && mode == 0)
	{
		ORDER->sym = ft_strdup(EXEC->sym[0]);
		dprintf(2, "%s\n", ORDER->sym);
	}
	else
		ORDER->sym = NULL;
}*/

/*void		exec_command(void)
{
	int		status;
	t_order		*temp_command;
	t_order		*temp_command2;
	t_order		*temp_command_next;
	pid_t	gpid;
	pipe(descrf);
	pipe(descrf_two);
	int		j;
	int		close_fd;

	j = 0;
	//EXEC->pid_exec = 0;
	//EXEC->gpid = 0;
	EXEC->ret = 0;
	while (ORDER->prev)
		ORDER = ORDER->prev;
	temp_command2 = ORDER;
	while (ORDER->next)
		ORDER = ORDER->next;
	ORDER = temp_command2;
	if (!EXEC->right)
	{
		//dprintf(2, "MABITE= %s\n", EXEC->left->tab_test[0]);
		if (EXEC->left->type == DESCR)
		{
			//modif_descr(EXEC->left->);
			EXEC->left = EXEC->left->next;
		}
		if (EXEC->left->next)
		{
			dprintf(2, "MABITE= %s\n", EXEC->left->next->tab_test[0]);
			dprintf(2, "MABITE2= %d\n", EXEC->left->next->type);
		}
		execute_pipe_two(0);
		return ;
	}
	while (ORDER)
	{
		while (ORDER && ORDER->sym && ORDER->sym[0] == '|')
		{
			descrf[0] = descrf_two[0];
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
		EXEC->ret = 1;
}*/

void		execute_ast(t_tree *tree, t_last *list_command)
{
	/*if (tree->left)
		execute_ast(tree->left, tab_arg);
	if (tree->type == OP)
		EXEC->sym = ft_strdup(tree->cmd);
	if (!tree->left)
	{
		if (!tree->left)
			EXEC->left = tab_arg;
		else
			EXEC->right = tab_arg;
	}
	if (EXEC->left && EXEC->right)
	{
		if (its_separator(EXEC->sym))
		{
			//add_to_exec(1);
			if (EXEC->ret == 0)
			{
				exec_command();
			}
			if ((EXEC->ret == 1 && its_AND(EXEC->sym)) || (EXEC->ret == -1 && its_OR(EXEC->sym)))
				EXEC->ret = 0;
		}
		//else
		//	add_to_exec(0);
		EXEC->left = EXEC->right;
		EXEC->right = NULL;
		return ;
	}
	if (tree->type == OP && its_separator(tree->cmd))
		EXEC->sym = tree->cmd;
	if (tree->right)
		execute_ast(tree->right, tab_arg);*/
	return ;
}
