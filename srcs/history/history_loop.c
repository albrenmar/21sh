/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:41:21 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		get_last(void)
{
	t_hist	*history;

	history = g_tracking.mysh->hist;
	if (!history)
		return (0);
	while (history->next)
		history = history->next;
	return (history->index);
}

t_hist	*get_hist_nbr(int i)
{
	t_hist	*history;

	history = g_tracking.mysh->hist;
	if (!history)
		return (0);
	while (history->previous)
		history = history->previous;
	if (!history)
		return (0);
	while (history)
	{
		if (history->index == i)
			return (history);
		history = history->next;
	}
	return (history);
}

int		replace_str(int i)
{
	t_hist	*history;

	history = g_tracking.mysh->hist;
	if (!history)
		return (0);
	while (history)
	{
		if (history->index == i)
		{
			if (ft_strlen(history->line) > 0)
			{
				ctrl_c();
				add_to_str(ft_strdup(history->line));
			}
			return (0);
		}
		history = history->next;
	}
	return (0);
}

int		history_up(void)
{
	char	*comp;
	t_hist	*history;
	int		i;

	if (g_tracking.quotes != 0)
		return (0);
	g_tracking.pos->abs = utf_strlen(g_tracking.str);
	back_to_pos();
	if (g_tracking.histindex > 1)
		g_tracking.histindex--;
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	comp = ft_strdup(g_tracking.str);
	i = ft_strlen(comp);
	replace_str(history->index);
	ft_free(comp);
	return (0);
}

int		history_down(void)
{
	char	*comp;
	t_hist	*history;
	int		i;

	if (g_tracking.quotes != 0)
		return (0);
	if (g_tracking.histindex == 1)
		g_tracking.histindex++;
	if (g_tracking.histindex <= g_tracking.histmax)
		g_tracking.histindex++;
	if (g_tracking.histindex == g_tracking.histmax + 1)
	{
		comp = ft_strdup(g_tracking.str);
		ctrl_c();
		ft_free(comp);
	}
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	comp = ft_strdup(g_tracking.str);
	i = ft_strlen(comp);
	replace_str(history->index);
	ft_free(comp);
	return (0);
}
