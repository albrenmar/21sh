/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/14 09:01:44 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

t_order		*new_order(void)
{
	t_order		*order;

	order = ft_memalloc(sizeof(t_order));
	order->command = NULL;
	order->next = NULL;
	order->prev = NULL;
	order->temp_command = NULL;
	return (order);
}

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

void		add_to_exec(int mode)
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
	ORDER->command = copy_tab(g_tracking.mysh->exec->left);
	if (EXEC->sym && mode == 0)
		ORDER->sym = ft_strdup(g_tracking.mysh->exec->sym[0]);
	else
		ORDER->sym = NULL;
}

void		exec_command(t_env *st_env, t_jobs *job)
{
	int		status;
	pid_t	jpid;
	pipe(descrf);
	pipe(descrf_two);
	int		close_fd;


	// EXEC->pid_exec = 0;
	// EXEC->gpid = 0;
	while (ORDER->prev)
		ORDER = ORDER->prev;
	if (!ORDER->next)
		return (execute_two(st_env, 2, job));
	while (ORDER)
	{
		while (ORDER && ORDER->sym && ORDER->sym[0] == '|' && ORDER->next)
		{
			descrf[0] = descrf_two[0];
			descrf[1] = descrf_two[1];
			pipe(descrf_two);
			execute_pipe(st_env, job);
			ORDER = ORDER->next;
		}
		while (ORDER && ORDER->sym && ORDER->sym[0] == '>' && ORDER->next && ORDER->next->sym && ORDER->next->sym[0] == '>')
		{
			ORDER = ORDER->next;
			close_fd = open(ORDER->command[0], O_CREAT | O_TRUNC, 0644);
			close(close_fd);
			}
		if (ORDER && (!ORDER->sym || ORDER->sym[0] == '>') && EXEC->ret != -1)
		{
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
			if (ORDER && ORDER->sym && ORDER->sym[0] == '>')
			{
				close(1);
				open(ORDER->next->command[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
				ORDER->temp_command = ORDER;
				while (ORDER->prev && ORDER->prev->sym[0] != '|')
					ORDER = ORDER->prev;
			}
			execute_two(st_env, 2, job);
			ORDER = ORDER->next;
		}
	}
}

void		execute_ast(t_tree *tree, t_tab_arg *tab_arg, t_env *st_env, t_jobs *job)
{
	if (tree->left)
		execute_ast(tree->left, tab_arg, st_env, job);
	if (/*!g_tracking.mysh->exec->sym &&*/ tree->type == OP)
		g_tracking.mysh->exec->sym = tree->cmd;
	if ((!g_tracking.mysh->exec->left || !g_tracking.mysh->exec->right) && !tree->left)
	{
		if (!g_tracking.mysh->exec->left)
			g_tracking.mysh->exec->left = tree->cmd;
		else
			g_tracking.mysh->exec->right = tree->cmd;
	}
	if (g_tracking.mysh->exec->left && g_tracking.mysh->exec->right)
	{
		if ((ft_strlen(EXEC->sym[0]) == 2) && ((EXEC->sym[0][0] == '|') || EXEC->sym[0][0] == '&'))
		{
			add_to_exec(1);
			if (EXEC->ret == 0)
				exec_command(st_env, job);
			if ((EXEC->ret == 1 && EXEC->sym[0][0] == '&') || (EXEC->ret == -1 && EXEC->sym[0][0] == '|'))
			{
				EXEC->ret = 0;
			}
			ORDER = NULL;
		}
		else
			add_to_exec(0);
		//execute();
		g_tracking.mysh->exec->left = g_tracking.mysh->exec->right;
		g_tracking.mysh->exec->right = NULL;
		return ;
	}
	if (/*!g_tracking.mysh->exec->sym && */tree->type == OP &&
			(ft_strlen(tree->name) != 2 || (tree->name[0] != '|' && tree->name[0] != '&')))
		g_tracking.mysh->exec->sym = tree->cmd;
	if (tree->right)
		execute_ast(tree->right, tab_arg, st_env, job);
	return ;
}
