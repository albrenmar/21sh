/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/24 18:28:31 by alsomvil         ###   ########.fr       */
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
	}
	return ;
}

void		create_ast(t_tree *tree, t_last *list_command)
{
	t_last	*separator;

	print_last(list_command);
	while (list_command->next)
	{
		printf("TEST DE FOU\n");
		list_command = list_command->next;
	}
	while (list_command->prev)
	{
		printf("TEST DE FOU2222\n");
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
	printf("TEST DE FOU3333\n");
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
	{
		printf("TEST DE FOU44444\n");
		print_last(tree->list_cmd);
		exec_command(tree->list_cmd, 0, job);
	}
	return ;
}
