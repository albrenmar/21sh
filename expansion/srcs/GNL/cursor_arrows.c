/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 04:48:12 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/05 15:13:37 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	move_left(void)
{
	int		i;
	int		x;
	int		y;
	int		ab;

	ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	x = ab % g_tracking.terminfo->sizex;
	i = 0;
	if (g_tracking.pos->abs > 0 && g_tracking.str != NULL)
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
	if (g_tracking.str != NULL)
	{
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
}

void	move_up(void)
{
	int		x;

	x = g_tracking.terminfo->sizex;
	if (check_up() == 0)
	{
		g_tracking.pos->abs -= x;
		tputs(tgetstr("up", NULL), 1, yan_putchar);
		g_tracking.pos->y--;
	}
	else
	{
		print_line();
		g_tracking.pos->abs = 0;
		back_to_pos();
	}
}

void	move_down(void)
{
	int		x;

	x = g_tracking.terminfo->sizex;
	print_line();
	if (check_down() == 0)
		g_tracking.pos->abs += x;
	else
		g_tracking.pos->abs = utf_strlen(g_tracking.str);
	back_to_pos();
}