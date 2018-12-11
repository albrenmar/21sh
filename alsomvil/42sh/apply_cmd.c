/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/05 05:04:32 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_cmd *cmd, char **env)
{
	t_tree	*tree;
	int		have_symbol;

	tree = ft_memalloc(sizeof(t_tree));
	while (cmd->beginlist->name)
	{
		if ((have_symbol = search_symbol(cmd->beginlist->name)))
			tree = ft_create_tree(cmd->beginlist->name, tree);
		else
			apply_builtin(st_tab, st_env, cmd->beginlist->name, env);
		if (have_symbol)
			apply_builtin_tree(st_tab, st_env, tree, env);
		cmd->beginlist = cmd->beginlist->next;
	}
}
