/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_page.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/12 04:49:41 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	set_up_page(void)
{
	int		nb;
	int		page;

	nb = lstcontainer_size(g_tracking.aut->comp_list);
	page = 3 * g_tracking.aut->col_nbr;
	g_tracking.aut->per_page = page;
	g_tracking.aut->page_nbr = nb / page;
	g_tracking.aut->active_page = 0;
}