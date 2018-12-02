/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 04:48:12 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/02 05:02:33 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	move_left(void)
{
	int		i;
	int		x;
	int		y;
	int		ab;

	ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	x = ab % g_tracking.terminfo->sizex;
	i = 0;
	if (g_tracking.pos->abs > 0)
	{
		g_tracking.pos->abs -= 1;
		if (x > 0)
			tputs(tgetstr("le", NULL), 1, yan_putchar);
		else
		{
			tputs(tgetstr("le", NULL), 1, yan_putchar);
			g_tracking.pos->y--;
		}
	}
}

void	move_right(void)
{
	int		i;
	int		x;
	int		y;
	int		ab;

	i = 0;
	if (g_tracking.pos->abs < (utf_strlen(g_tracking.str)))
	{
		g_tracking.pos->abs += 1;
        ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	    x = ab % g_tracking.terminfo->sizex;
		if (x != 0)
			tputs(tgetstr("nd", NULL), 1, yan_putchar);
		else
		{
			tputs(tgetstr("cr", NULL), 1, yan_putchar);
            tputs(tgetstr("do", NULL), 1, yan_putchar);
			g_tracking.pos->y++;
		}
	}
}