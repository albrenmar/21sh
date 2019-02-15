/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/15 09:21:35 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		sig_int_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		// // print_prompt_pwd();
		ft_putstr(g_tracking.prompt);
		// ioctl(0,TIOCSTI, "\1\0");
		signal(SIGINT, sig_int_handler);
	}
}

void		suspend_signal_handler(void)
{
	signal(SIGTSTP, SIG_DFL);
}

void		stop_signal_handler(void)
{
	exit(EXIT_SUCCESS);
}

void		signal_handler(int signo)
{
	if (signo == SIGTSTP)
		return ;
	else if (signo == SIGINT || signo == SIGABRT || signo == SIGSTOP
			|| signo == SIGKILL || signo == SIGQUIT || signo == SIGSEGV)
		return ;
	else if (signo == SIGCONT)
	{
	}
	else if (signo == SIGWINCH)
	{
	}
}

void		set_process_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void		set_shell_signal_handlers(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	// signal(SIGCHLD, SIG_IGN);
}

void		set_signal_handlers(void)
{
	// signal(SIGWINCH, signal_handler);
	signal(SIGINT, sig_int_handler);
	signal(SIGSTOP, signal_handler);
	// signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}
