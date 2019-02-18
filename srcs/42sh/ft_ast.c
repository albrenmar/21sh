/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/18 04:06:50 by alsomvil         ###   ########.fr       */
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
	tree->list_cmd = NULL;
	tree->cmd = NULL;
	tree->right = NULL;
	tree->left = NULL;
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
		if (ft_strlen(list->name) == 2 && (list->name[0] == '|' || list->name[0] == '&'))
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
	}
	return ;
}

void		create_ast(t_tree *tree, t_last *list_command)
{
	t_last	*separator;
	while (list_command->next)
		list_command = list_command->next;
	while (list_command->prev)
	{
		if ((separator = search_OR_AND(list_command)))
		{
			tree->type = SEP;
			tree->cmd = ft_strdup(separator->name);
			tree->left = new_branch();
			tree->right = new_branch();
			separator->prev->next = NULL;
			create_ast(tree->left, separator->prev);
			separator->prev = NULL;
			separator->next->prev = NULL;
			create_ast(tree->right, separator->next);
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

	//print_last(list_command);
	tree = new_branch();
	create_ast(tree, list_command);
	//affich_ast(tree);
	execute_ast(tree, list_command);
	exit (0);
	return ;
}
