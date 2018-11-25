/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:26:48 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/25 16:33:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	correct_pos(void) 
{
	int		ab;

	ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	g_tracking.pos->x = ab % g_tracking.terminfo->sizex;
	g_tracking.pos->y = (ab / g_tracking.terminfo->sizex) + g_tracking.pos->legacy;
}

void	update_pos(void)
{
	int		x;
	int		y;
	char	*test;

	test = tgetstr("cm", NULL);
	correct_pos();
	x = g_tracking.pos->x;
	y = g_tracking.pos->y;
	tputs(tgoto(test, x, y), 1, yan_putchar);
}