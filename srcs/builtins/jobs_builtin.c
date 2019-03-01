/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/25 12:44:10 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			jobs_builtin_parser(t_jobs *tmp, int optionl, int optionp, char *hold)
{
	int		i;
	int		j;
	int		place;
	int		mode;
	i = 1;
	mode = 0;
	place = 0;
	if (g_tracking.g_tab_exec[1])
	{
		while (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '-')
		{
			if (!g_tracking.g_tab_exec[i][1])
				return (errors_jobs('a', 0, 0));
			j = 1;
			while (g_tracking.g_tab_exec[i][j] != '\0')
			{
				if (g_tracking.g_tab_exec[i][j] != 'l' && g_tracking.g_tab_exec[i][j] != 'p')
					return (errors_jobs(g_tracking.g_tab_exec[i][j], 0, 1));
				else if (g_tracking.g_tab_exec[i][j] == 'l')
					optionl = 1;
				else if (g_tracking.g_tab_exec[i][j] == 'p')
					optionp = 1;
				j++;
			}
			i++;
		}
		if (optionp)
			j = 2;
		else if (optionl)
			j = 1;
		if (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '%')
		{
			while (g_tracking.g_tab_exec[i] && g_tracking.g_tab_exec[i][0] == '%')
			{
				hold = parse_job_number(g_tracking.g_tab_exec[i]);
				if (job_exists(parse_job_sign(g_tracking.g_tab_exec[i])))
					jobs_builtin_output(tmp, 1, parse_job_sign(g_tracking.g_tab_exec[i]), j);
				else if (hold && job_exists(ft_atoi(hold)))
					jobs_builtin_output(tmp, 1, ft_atoi(hold), j);
				else if (hold)
					errors_jobs('a', ft_atoi(hold), 2);
				else
					errors_jobs('a', 0, 2);
				i++;
			}
			return (0);
		}
		else
		{
			jobs_builtin_output(tmp, 0, 0, j);
			return (0);
		}
	}
	jobs_builtin_output(tmp, 0, 0, 0);
	return (0);
}

void		jobs_builtin_output(t_jobs *tmp, int mode, int number, int options)
{
	while (tmp && tmp->next)
	{
		if (mode == 0 || (mode == 1 && number == tmp->place))
		{
			if (options != 2)
			{
				ft_putchar('[');
				ft_putnbr(tmp->place);
				ft_putchar(']');
				if (tmp->current == 1)
					ft_putchar('+');
				else if (tmp->currentback == 1)
					ft_putchar('-');
				else
					ft_putchar(' ');
				ft_putchar(' ');
			}
			if (options == 1 || options == 2)
				ft_putnbr(tmp->jpid);
			ft_putchar(' ');
			if (options == 2)
				ft_putchar('\n');
			if (options != 2)
			{
				if (tmp->background == 1)
					ft_putstr("Running");
				if (options != 1 && tmp->t_cmd->stopped == 1)
					ft_putstr("Stopped");
				else if (options == 1)
					ft_putstr("Suspended");
				else
					ft_putstr("       ");
				ft_putstr("           ");
				ft_putstr(tmp->name);
				ft_putchar(' ');
				if (tmp->background == 1)
					ft_putchar('&');
				ft_putstr("      ");
				if (ft_strcmp(tmp->wd, getcwd(NULL, 42)))
				{
					ft_putstr("(wd: ");
					ft_putstr(tmp->wd);
					ft_putendl(")  ");
				}
				else
					ft_putchar('\n');
				if (mode == 1 && tmp->place == number)
					return ;
			}
		}
		tmp = tmp->next;
	}
}

int			jobs_builtin(void)
{
	t_jobs	*tmp;
	int		optionl;
	int		optionp;
	char	*place;

	optionl = 0;
	optionp = 0;
	place = NULL;
	tmp = g_tracking.jobs;
	if (tmp && tmp->next)
		return (jobs_builtin_parser(tmp, optionl, optionp, place));
	ft_putendl("No jobs bro");
	return (1);
}