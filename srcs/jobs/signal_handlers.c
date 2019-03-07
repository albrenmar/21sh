/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/07 05:02:22 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

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
	int			i;
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

void					set_process_signal_handlers(void)
{
	// signal(SIGSEGV, SIG_IGN);
	// signal(SIGABRT, SIG_IGN);
	// signal(SIGKILL, SIG_DFL);
	// signal(SIGSTOP, SIG_DFL);
	struct sigaction	psa;
    psa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGQUIT, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGTSTP, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGCONT, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGTTOU, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGTTIN, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGTTOU, &psa, NULL);
	psa.sa_handler = SIG_DFL;
    sigaction(SIGCHLD, &psa, NULL);
}

void					set_shell_signal_handlers(void)
{
	// signal(SIGSEGV, SIG_IGN);
	// signal(SIGABRT, SIG_IGN);
	// signal(SIGKILL, SIG_IGN);
	// signal(SIGSTOP, SIG_IGN);
	struct sigaction	psa;

    psa.sa_handler = sig_int_handler;
    sigaction(SIGINT, &psa, NULL);
	psa.sa_handler = sig_winch_handler;
    sigaction(SIGWINCH, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGCONT, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGTTIN, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGTTOU, &psa, NULL);
	psa.sa_handler = SIG_IGN;
    sigaction(SIGCHLD, &psa, NULL);
}
