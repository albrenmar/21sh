/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/17 04:30:24 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_tree *tree)
{
	int		i;

	i = 0;
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree->str1);
	free(tree->str2);
	ft_strdel(tree->str_command1);
	ft_strdel(tree->str_command2);
	while (tree->cmd1[i])
		ft_strdel(&tree->cmd1[i++]);
	ft_memdel(&tree->cmd1);
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
