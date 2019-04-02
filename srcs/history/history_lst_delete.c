/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:35:43 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/02 17:29:32 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			search_index_to_delete_neg(int index)
{
	long tmp;

	tmp = 1;
	tmp += index;
	if (!g_tracking.mysh->hist || g_tracking.mysh->hist->index == 0\
	|| !g_tracking.mysh->hist->line)
		return (0);
	if (index == 0)
		return (0);
	while (g_tracking.mysh->hist->next)
		g_tracking.mysh->hist = g_tracking.mysh->hist->next;
	while (g_tracking.mysh->hist->previous && tmp-- != 0)
		g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
	if (g_tracking.mysh->hist->index == index)
		return (index);
	return (0);
}

int			search_index_to_delete(int index)
{
	if (!g_tracking.mysh->hist || g_tracking.mysh->hist->index == 0\
	|| !g_tracking.mysh->hist->line)
		return (0);
	if (index == 0)
		return (0);
	while (index < g_tracking.mysh->hist->index\
	&& g_tracking.mysh->hist->previous)
		g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
	while (index > g_tracking.mysh->hist->index && g_tracking.mysh->hist->next)
		g_tracking.mysh->hist = g_tracking.mysh->hist->next;
	if (g_tracking.mysh->hist->index == index)
		return (index);
	return (0);
}

int			delete_index_special(void)
{
	t_hist *tmp;

	if (!g_tracking.mysh->hist->previous && !g_tracking.mysh->hist->next)
	{
		g_tracking.mysh->hist = hist_free();
		return (1);
	}
	if (!g_tracking.mysh->hist->previous\
		&& g_tracking.mysh->hist->next)
	{
		tmp = g_tracking.mysh->hist;
		g_tracking.mysh->hist = g_tracking.mysh->hist->next;
		ft_strdel(&tmp->line);
		free(tmp);
		g_tracking.mysh->hist->previous = NULL;
		g_tracking.mysh->hist = hist_remap_index(g_tracking.mysh->hist);
		return (1);
	}
	if (g_tracking.mysh->hist->previous\
		&& !g_tracking.mysh->hist->next)
	{
		g_tracking.mysh->hist = hist_delete_last(g_tracking.mysh->hist);
		g_tracking.mysh->hist = hist_remap_index(g_tracking.mysh->hist);
		return (1);
	}
	return (0);
}

int			delete_index(int index)
{
	t_hist *tmp;

	if (g_tracking.mysh->hist && g_tracking.mysh->hist->index == index)
	{
		if (delete_index_special())
			return (1);
		if (g_tracking.mysh->hist->previous && g_tracking.mysh->hist->next)
		{
			tmp = g_tracking.mysh->hist;
			tmp->previous->next = tmp->next;
			tmp->next->previous =\
			tmp->previous;
			ft_strdel(&tmp->line);
			free(tmp);
			tmp = NULL;
			g_tracking.mysh->hist = hist_remap_index(g_tracking.mysh->hist);
			return (1);
		}
	}
	return (0);
}

void		history_builtin_delete_index(int j)
{
	char	*tmp;
	long	index;

	index = 0;
	if (g_tracking.g_tab_exec[2]\
	&& ft_isdigit_str(g_tracking.g_tab_exec[2]) && g_tracking.g_tab_exec[3] == NULL)
	{
		if (delete_index_dispatch(ft_atoi(g_tracking.g_tab_exec[2])) == 0)
			return (ft_putendl("History position out of range"));
	}
	else if (g_tracking.g_tab_exec[2]\
	&& ft_isdigit_str(g_tracking.g_tab_exec[2]) && g_tracking.g_tab_exec[3]\
	&& ft_isdigit_str(g_tracking.g_tab_exec[3]))
	{
		if (delete_dispatch_multiple(ft_atoi(g_tracking.g_tab_exec[2])\
		, ft_atoi(g_tracking.g_tab_exec[3])) == 0)
			return (ft_putendl("History position out of range"));
	}
	else
		return (ft_putendl(\
		"history -d [index] || history -d [begin index] [end index]"));
}
