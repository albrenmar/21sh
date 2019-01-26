/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:11:02 by mjose             #+#    #+#             */
/*   Updated: 2019/01/26 04:56:24 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <termios.h>

typedef struct			s_process
{
	char				**argv;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_job
{
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
	t_ast				*ast;
	struct s_job		*next;
	struct s_job		*prev;
}						t_job;

t_process	*new_process(void);
t_job		*new_job(void);

#endif
