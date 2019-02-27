/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/13 08:39:32 by alsomvil         ###   ########.fr       */
=======
/*   Updated: 2019/02/24 18:44:35 by alsomvil         ###   ########.fr       */
>>>>>>> mjose.merge
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define ORDER g_tracking.mysh->order
#define EXEC g_tracking.mysh->exec

t_tree		*new_branch(void)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
<<<<<<< HEAD
	tree->name = NULL;
	tree->cmd = NULL;
	tree->prev = NULL;
	tree->right = NULL;
	tree->left = NULL;
	return (tree);
}

void		create_ast(t_tree *tree, t_tab_arg *tab_arg)
{
	t_tab_arg	*temp;
	t_tab_arg	*temp_left;
	t_tab_arg	*temp_right;

	temp = NULL;
	temp_left = tab_arg;
	while (tab_arg->next)
		tab_arg = tab_arg->next;
	while (tab_arg->prev)
	{
		if ((temp == NULL) && tab_arg->type == OP)
			temp = tab_arg;
		else if (tab_arg->type == OP)
		{
			if (tab_arg->tab_test[0][0] == ';' || tab_arg->tab_test[0][0] == '&')
				temp = tab_arg;
		}
		tab_arg = tab_arg->prev;
	}
	if (temp)
	{
		if (temp->prev)
			temp->prev->next = NULL;
		temp_right = temp->next;
		temp_right->prev = NULL;
	}
	else
	{
		tree->name = ft_strdup(tab_arg->tab_test[0]);
		tree->cmd = tab_arg->tab_test;
		return ;
	}
	tree->type = temp->type;
	tree->name = ft_strdup(temp->tab_test[0]);
	tree->cmd = temp->tab_test;
	if (temp_left)
	{
		tree->left = new_branch();
		tree->left->prev = tree;
		create_ast(tree->left, temp_left);
	}
	if (temp_right)
	{
		tree->right = new_branch();
		tree->right->prev = tree;
		create_ast(tree->right, temp_right);
=======
	tree->list_cmd = NULL;
	tree->cmd = NULL;
	tree->right = NULL;
	tree->left = NULL;
	tree->prev = NULL;
	return (tree);
}

t_last	*search_OR_AND(t_last *list)
{
	t_last	*temp;
	t_last	*begin;

	begin = list;
	temp = NULL;
	while (list->prev)
	{
		if ((ft_strlen(list->name) == 2 && (list->name[0] == '|' || list->name[0] == '&')) || (ft_strlen(list->name) == 1 && (list->name[0] == '&' || list->name[0] == ';')))
		{
			temp = list;
			list = begin;
			return (temp);
		}
		list = list->prev;
	}
	return (NULL);
}

void		affich_ast(t_tree *tree)
{
	if (tree->type == SEP)
	{
		if (tree->left && tree->left->type != SEP)
		{
			while (tree->left->list_cmd)
			{
				printf("[%s]\n", tree->left->list_cmd->name);
				tree->left->list_cmd = tree->left->list_cmd->next;
			}
		}
		else if (tree->left && tree->left->type == SEP)
			affich_ast(tree->left);
		printf("[%s]\n", tree->cmd);
		if (tree->right && tree->right->type != SEP)
		{
			while (tree->right->list_cmd)
			{
				printf("[%s]\n", tree->right->list_cmd->name);
				tree->right->list_cmd = tree->right->list_cmd->next;
			}
		}
		else if (tree->right)
			affich_ast(tree->right);
>>>>>>> mjose.merge
	}
	return ;
}

<<<<<<< HEAD
void		init_ast(void)
{
	g_tracking.mysh->exec = ft_memalloc(sizeof(t_exec));
	g_tracking.mysh->exec->left = NULL;
	g_tracking.mysh->exec->right = NULL;
	g_tracking.mysh->exec->sym = NULL;
}

void		ft_ast(t_tab_arg *tab_arg)
{
	t_tree	*tree;
	pid_t	gpid;
	pipe(descrf);
	pipe(descrf_two);

	tree = new_branch();
	create_ast(tree, tab_arg);
	init_ast();
	execute_ast(tree,tab_arg);
	add_to_exec(1);
	if (EXEC->ret == 0)
		exec_command();
	ORDER = NULL;
=======
void		create_ast(t_tree *tree, t_last *list_command)
{
	t_last	*separator;

	//print_last(list_command);
	while (list_command->next)
		list_command = list_command->next;
	while (list_command->prev)
	{
		if ((separator = search_OR_AND(list_command)))
		{
			tree->type = SEP;
			tree->cmd = ft_strdup(separator->name);
			tree->left = new_branch();
			tree->left->prev = tree;
			tree->right = new_branch();
			tree->right->prev = tree;
			separator->prev->next = NULL;
			create_ast(tree->left, separator->prev);
			separator->prev = NULL;
			if (separator->next)
			{
				separator->next->prev = NULL;
				create_ast(tree->right, separator->next);
			}
			separator->next = NULL;
			return ;
		}
		list_command = list_command->prev;
	}
	tree->type = CMD;
	tree->list_cmd = list_command;
	return ;
}

void		ft_ast(t_last *list_command)
{
	t_tree	*tree;
	pipe(descrf);
	pipe(descrf_two);
	t_jobs	*job;

	tree = new_branch();
	create_ast(tree, list_command);
	if (tree->type == SEP)
	{
		execute_ast(tree, job);
	}
	else
		exec_command(tree->list_cmd, 0, job);
>>>>>>> mjose.merge
	return ;
}
