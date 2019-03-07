/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:41:21 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 04:01:56 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/01/22 23:27:52 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

# include "sh42.h"

int		get_last()
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
	while (history)
	{
		if (history->index == i)
			return (history);
		history = history->next;
	}
	return (g_tracking.mysh->hist);
}

int		replace_str(int i, char *comp)
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
				rem_str(comp);
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
	char	*cur;
	t_hist	*history;
	int		i;

<<<<<<< HEAD
	g_tracking.pos->abs = utf_strlen(g_tracking.str);
	back_to_pos();
=======
>>>>>>> alsomvil
	if (g_tracking.histindex > 1)
		g_tracking.histindex--;
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	comp = ft_strdup(g_tracking.str);
	i = ft_strlen(comp);
	replace_str(history->index, comp);
	free(comp);
	return (0);
}

int		history_down(void)
{
	char	*comp;
	char	*cur;
	t_hist	*history;
	int		i;

	if (g_tracking.histindex == 1)
		g_tracking.histindex++;
	if (g_tracking.histindex <= g_tracking.histmax)
		g_tracking.histindex++;
	if (g_tracking.histindex == g_tracking.histmax + 1)
		{
			comp = ft_strdup(g_tracking.str);
			rem_str(comp);
			free(comp);
		}
	history = get_hist_nbr(g_tracking.histindex);
	if (!history)
		return (0);
	comp = ft_strdup(g_tracking.str);
	i = ft_strlen(comp);
	replace_str(history->index, comp);
	free(comp);
	return (0);
}