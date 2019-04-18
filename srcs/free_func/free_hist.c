/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 04:38:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/02 06:55:26 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		free_hist(void)
{
	t_hist	*next;

	if (!g_tracking.mysh->hist)
		return ;
	while (g_tracking.mysh->hist->previous)
		g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
	while (g_tracking.mysh->hist)
	{
		if (g_tracking.mysh->hist->line)
		{
			ft_free(g_tracking.mysh->hist->line);
			g_tracking.mysh->hist->line = NULL;
		}
		next = g_tracking.mysh->hist->next;
		if (!g_tracking.mysh->hist || !g_tracking.mysh->hist->line)
			ft_free(g_tracking.mysh->hist);
		g_tracking.mysh->hist = next;
	}
	g_tracking.mysh->hist = NULL;
}
