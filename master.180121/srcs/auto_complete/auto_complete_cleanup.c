/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 06:52:13 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/20 07:17:35 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	clean_up_pages(void)
{
	if (g_tracking.aut->page_lst)
	{
		ft_lstdel(g_tracking.aut->page_lst->firstelement, 0);
		free(g_tracking.aut->page_lst);
	}
}

void	clean_up_autoc(void)
{
	free(g_tracking.aut->word);
	g_tracking.aut->word = NULL;
	free(g_tracking.aut->menuline);
	g_tracking.aut->menuline = NULL;
	free(g_tracking.aut->path);
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->to_free)
	{
		free_all(g_tracking.aut->to_free, NULL);
		g_tracking.aut->to_free = NULL;
		ft_lstdel(g_tracking.aut->comp_list->firstelement, 0);
		free(g_tracking.aut->comp_list);
	}
	else
	{
		free_all(g_tracking.aut->comp_list, NULL);
		g_tracking.aut->comp_list = NULL;
	}
	clean_up_pages();
	free(g_tracking.aut);
}