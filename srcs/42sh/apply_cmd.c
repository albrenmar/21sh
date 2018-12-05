/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 17:30:12 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_cmd *cmd, char **env)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
	while (cmd->beginlist->name)
	{
		if (search_symbol(cmd->beginlist->name))
			tree = ft_create_tree(cmd->beginlist->name, tree);
		else
			apply_builtin(st_tab, st_env, cmd->beginlist->name, env);
		cmd->beginlist = cmd->beginlist->next;
	}
}
