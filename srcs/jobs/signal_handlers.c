/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		sig_quit_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putendl("Quit: 3");
		signal(SIGQUIT, sig_quit_handler);
	}
}

void		sig_int_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, sig_int_handler);
	}
}

void		sig_winch_handler(int signo)
{
	int			y;

	if (signo == SIGWINCH)
	{
		get_size();
		update_pos();
		y = utf_strlen(g_tracking.str);
		y += g_tracking.pos->prompt;
		g_tracking.pos->y = y / g_tracking.terminfo->sizex;
		if (g_tracking.aut)
			ioctl(STDERR_FILENO, TIOCSTI, "'");
		signal(SIGWINCH, sig_winch_handler);
	}
}

void		set_process_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void		set_shell_signal_handlers(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGWINCH, sig_winch_handler);
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
}
