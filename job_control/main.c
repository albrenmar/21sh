/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 00:56:21 by mjose             #+#    #+#             */
/*   Updated: 2019/01/17 05:45:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/includes/minishell.h"

typedef struct	s_lproc
{
	int				num_proc;
	int				pid;
	int				status;
	struct s_lproc	*next;
}				t_lproc;

	t_lproc		*tmp_proc;
	int			id = 0;

void		kill_child(int signum)
{
	//kill(tmp_proc->pid, SIGINT);
	signum = SIGINT;
	kill(tmp_proc->pid, signum);
	wait(&tmp_proc->status);
}

void	stop_child(int signum)
{
//	kill(tmp_proc->pid, SIGSTOP);
	signum = SIGSTOP;
	kill(tmp_proc->pid, signum);
	wait(&tmp_proc->status);
	if (WIFSTOPPED(tmp_proc->status))
	{
		ft_putchar('[');
		ft_putnbr(tmp_proc->num_proc);
		ft_putchar(']');
		ft_putendl("\t+ suspended\t");
	}
}

t_lproc		*init_proc(void)
{
	t_lproc		*proc;

	proc = (t_lproc *)malloc(sizeof(t_lproc));
	proc->num_proc = 0;
	proc->pid = 0;
	proc->status = 0;
	proc->next = NULL;
	return (proc);
}

int	crt_child(t_lproc **list_proc)
{
	t_lproc			*new_proc;

	new_proc = init_proc();
	new_proc->num_proc = ++id;
	tmp_proc = new_proc;
//	if (fork() == 0)
//	{
		ft_putendl("Presiona CTRL+C o CTRL+Z");
		if ((tmp_proc->pid = fork()) == 0)
			while (1);
		else
		{
			signal(SIGINT, &kill_child);
			signal(SIGTSTP, &stop_child);
			wait(&tmp_proc->status);
//			exit(0);
		}
//	}
//	else
	tmp_proc->next = ft_memalloc(sizeof(t_lproc));
	if (WIFSTOPPED(tmp_proc->status))
	{
		tmp_proc = tmp_proc->next;
		list_proc = &tmp_proc;
		return (0);
	}
	tmp_proc = tmp_proc->next;
	list_proc = &tmp_proc;
	return (1);
}

int		main(void)
{
	t_lproc			*list_proc;

	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		if (crt_child(&list_proc))
			ft_putendl("Creo nuevo hijo.");
		else
			break ;
	}
}