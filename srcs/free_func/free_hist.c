/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 04:38:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/19 22:54:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		free_hist(void)
{
	t_hist	*hist;
	t_hist	*next;

	if (!g_tracking.mysh->hist)
		return ;
	hist = g_tracking.mysh->hist;
	while (hist->previous)
		hist = hist->previous;
	while (hist)
	{
		if (hist->line)
		{
			free(hist->line);
			hist->line = NULL;
		}
		next = hist->next;
		free(hist);
		hist = next;
	}
	g_tracking.mysh->hist = NULL;
}
