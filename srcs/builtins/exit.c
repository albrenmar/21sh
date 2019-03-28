/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/28 04:45:06 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void		free_keyval(t_lstcontainer *list)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (list)
	{
		tmp = ft_lstgetfirst(list->firstelement);
		while (tmp)
		{
			buf = tmp->content;
			if (buf)
			{
				free_and_null(buf->key);
				free_and_null(buf->value);
			}
			tmp = tmp->next;
		}
		ft_lstdel(list->firstelement, 1);
		free(list);
		list = NULL;
	}
}

void		clean_up_leaks(void)
{
	if (g_tracking.aut)
		clean_up_autoc();
	if (g_tracking.mysh->alias_lst)
	{
		free_keyval(g_tracking.mysh->alias_lst);
		g_tracking.mysh->alias_lst = NULL;
	}
	if (g_tracking.mysh->hist)
		ctrl_c();
	free(g_tracking.str);
	free(g_tracking.cpaste->line);
	g_tracking.str = NULL;
	free(g_tracking.terminfo);
	g_tracking.terminfo = NULL;
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	ft_strdel(&g_tracking.prompt);
	g_tracking.prompt = NULL;
	ft_strdel(&g_tracking.user);
	g_tracking.user = NULL;
	ft_strdel(&g_tracking.cwd);
	g_tracking.cwd = NULL;
}

int			ft_exit(int process, int exitcode)
{
	t_jobs	*tmp;

	if (process == 1)
	{
		tmp = g_tracking.jobs;
		while (tmp && tmp->next)
		{
			if (tmp->background == 1)
			{
				ft_putendl("There are still background jobs running!");
				return (1);
			}
			tmp = tmp->next;
		}
	}
	hist_save_file(g_tracking.mysh->hist);
	free_hist();
	clean_up_leaks();
	clean_up_leaks();
	empty_hash_table();
	free_all_jobs();
	exit(exitcode);
}
