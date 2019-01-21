/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/20 21:06:01 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	complete_usr_word(void)
{
	t_lstcontainer	*list;

	list = NULL;
	assign_type();
	list = build_ls();
	if (list != NULL)
	{
		build_comp(list);
		g_tracking.aut->to_add = NULL;
		if (g_tracking.aut->comp_list->firstelement != NULL)
		{
			get_max_size();
			rem_str(g_tracking.aut->word);
			set_up_page();
			completion_loop(g_tracking.aut->comp_list);
		}
	}
}