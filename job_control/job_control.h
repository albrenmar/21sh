/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 02:04:26 by mjose             #+#    #+#             */
/*   Updated: 2019/01/21 12:24:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "../minishell/includes/minishell.h"
# include <termios.h>

typedef struct		s_process
{
	char				**argv;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	struct s_process	*next;
}					t_process;

typedef struct		s_job
{
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
	struct s_job		*next;
}					t_job;

t_job				*g_first_job = NULL;
pid_t				g_shell_pgid;
struct termios		g_shell_tmodes;
int					g_shell_terminal;
int					g_shell_is_interactive;

t_job				*find_job (pid_t pgid);
int					job_is_stopped(t_job *job_list);
int					job_is_completed(t_job *job_list);
void				init_shell(void);
void				launch_process(t_process *process_list, pid_t pgid, int infile, int outfile, int errfile, int foreground);
void				launch_job(t_job *job_list, int foreground);
void				put_job_in_foreground(t_job *job_list, int cont);
void				put_job_in_background(t_job *job_list, int cont);

#endif
