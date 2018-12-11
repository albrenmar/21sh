/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/11 18:38:48 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree->str1);
	free(tree->str2);
	free(tree->symbol);
	free(tree);
}

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_list *list_cmd, char **env)
{
	t_tree	*tree;

	while (list_cmd->name)
	{
		tree = ft_memalloc(sizeof(t_tree));
		if (search_symbol(list_cmd->name))
			tree = ft_create_tree(list_cmd->name, tree);
		else
			apply_builtin(st_tab, st_env, list_cmd->name, env);
		list_cmd = list_cmd->next;
		free_tree(tree);
	}
}
