/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 06:52:13 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 00:29:04 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/03/01 07:10:11 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
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

<<<<<<< HEAD
void	clean_up_tofree(void)
{
	free_all(g_tracking.aut->to_free, NULL);
	g_tracking.aut->to_free = NULL;
	ft_lstdel(g_tracking.aut->comp_list->firstelement, 0);
	free(g_tracking.aut->comp_list);
}

=======
>>>>>>> alsomvil
void	clean_up_autoc(void)
{
	free(g_tracking.aut->word);
	g_tracking.aut->word = NULL;
	free(g_tracking.aut->menuline);
	g_tracking.aut->menuline = NULL;
	free(g_tracking.aut->path);
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->to_free)
<<<<<<< HEAD
		clean_up_tofree();
=======
	{
		free_all(g_tracking.aut->to_free, NULL);
		g_tracking.aut->to_free = NULL;
		ft_lstdel(g_tracking.aut->comp_list->firstelement, 0);
		free(g_tracking.aut->comp_list);
	}
>>>>>>> alsomvil
	else
	{
		free_all(g_tracking.aut->comp_list, NULL);
		g_tracking.aut->comp_list = NULL;
		free_all(g_tracking.aut->bin_lst, NULL);
		g_tracking.aut->bin_lst = NULL;
	}
	free_all(g_tracking.aut->var_lst, NULL);
	g_tracking.aut->var_lst = NULL;
	free(g_tracking.aut->to_add);
	clean_up_pages();
	free(g_tracking.aut);
	g_tracking.aut = NULL;
<<<<<<< HEAD
}
=======
}
>>>>>>> alsomvil
