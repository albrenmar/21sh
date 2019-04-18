/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mysh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 09:25:40 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 23:25:09 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		free_mysh(void)
{
	hist_save_file(g_tracking.mysh->hist);
	free_hist();
	if (g_tracking.mysh->alias_lst)
	{
		free_keyval(g_tracking.mysh->alias_lst);
		g_tracking.mysh->alias_lst = NULL;
	}
	free_keyval(g_tracking.mysh->env);
	free_keyval(g_tracking.mysh->set_env);
	ft_lstdel(g_tracking.key_list->firstelement, 1);
	ft_free(g_tracking.key_list);
	ft_lstdel(g_tracking.builtin_list->firstelement, 1);
	ft_free(g_tracking.builtin_list);
	free_tab(g_tracking.mysh->tab_env);
}
