/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:00:48 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/16 16:53:41 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		fg_bg(int sino)
{
	if (sino == SIGTSTP)
	{
		set_back_term();
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
	else if (sino == SIGCONT)
	{
		get_term();
		ft_siginit();
	}
}

void		handle_sin(int sino)
{
	char		*test;

	if (sino == SIGABRT || sino == SIGINT || sino == SIGKILL
	|| sino == SIGINT || sino == SIGQUIT)
	{
		set_back_term();
		exit(0);
	}
	if (sino == SIGTSTP || sino == SIGCONT)
		fg_bg(sino);
	if (sino == SIGWINCH)
	{
		g_tracking.pos->y = 0;
		clear_screen2();
		get_size();
		ft_putstr(">");
		ft_putstr(g_tracking.str);
		update_pos();
	}
}

void		ft_siginit(void)
{
/*	signal(SIGABRT, handle_sin);
	signal(SIGINT, handle_sin);
	signal(SIGSTOP, handle_sin);
	signal(SIGQUIT, handle_sin);
	signal(SIGKILL, handle_sin);
	signal(SIGCONT, handle_sin);
	signal(SIGTSTP, handle_sin);*/
	signal(SIGWINCH, handle_sin);
}
