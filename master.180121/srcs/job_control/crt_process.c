/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crt_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:48:18 by mjose             #+#    #+#             */
/*   Updated: 2019/01/26 09:12:49 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "minishell.h"
#include "job_control.h"

t_process	*new_process(void)
{
	t_process	*process;

	process = ft_memalloc(sizeof(t_process));
	process->argv = NULL;
	process->next = NULL;
	process->prev = NULL;
	return (process);
}

void		crt_process(t_process *processes, char *command, t_ast *ast)
{
	t_process	*first_proc;
	t_process	*prev;
	char		*true_command;
	first_proc = processes;
	prev = first_proc;
	if (!ast)
		processes->argv = ft_strsplit(command, ' ');
	else
	{
		true_command = command_wout_sym(command);
		processes->argv = ft_strsplit(true_command, ' ');
		ft_strdel(&true_command);
	}
}
