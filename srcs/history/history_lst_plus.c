/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:02:27 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/01 16:20:53 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_hist		*hist_remap_index(t_hist *hist)
{
	int i;

	i = 1;
	if (g_tracking.hist_first == 0)
	{
		hist = hist_remap_null(hist);
		g_tracking.mysh->hist = hist;
	}
	if (!hist)
		return (NULL);
	while (hist && hist->previous)
		hist = hist->previous;
	if (hist && hist->index == 0 && hist->next && hist->next->line)
		hist = hist->next;
	while (hist)
	{
		hist->index = i;
		i++;
		if (hist->next)
			hist = hist->next;
		else
			break ;
	}
	return (hist);
}

int			hist_delete_index_setup(t_hist *hist, int index)
{
	if (index < 1)
	{
		ft_putendl_fd("history position out of range", 2);
		return (1);
	}
	while (hist->index > index)
	{
		if (hist->previous == NULL)
		{
			ft_putendl_fd("history position out of range", 2);
			return (1);
		}
		hist = hist->previous;
	}
	while (hist->index < index)
	{
		if (hist->next == NULL)
		{
			ft_putendl_fd("history position out of range", 2);
			return (1);
		}
		hist = hist->next;
	}
	return (0);
}

t_hist		*hist_delete_index_check(t_hist *hist, int index)
{
	if (!(hist->previous) && !(hist->next))
		return (hist = hist_free());
	if (hist->previous == NULL)
	{
		hist = hist->next;
		free(hist->previous->line);
		free(hist->previous);
		return (hist);
	}
	else if (hist->next == NULL)
	{
		hist = hist->previous;
		free(hist->next->line);
		free(hist->next);
		return (hist);
	}
	return (NULL);
}

t_hist		*hist_delete_index(t_hist *hist, int index)
{
	t_hist	*tmp;

	if (!hist || (!hist->line && hist->index != 0))
		return (NULL);
	if ((hist_delete_index_setup(hist, index)) != 0)
		return (hist);
	if (hist && hist->index == index)
	{
		if ((hist = hist_delete_index_check(hist, index)) != NULL)
			return (hist);
		else
		{
			hist->previous->next = hist->next;
			hist->next->previous = hist->previous;
			free(hist->line);
			tmp = hist;
			hist = hist->previous;
			free(tmp);
			hist->next = NULL;
		}
	}
	hist = hist_remap_index(hist);
	return (hist);
}

t_hist		*hist_delete_last(t_hist *hist)
{
	t_hist *tmp;

	if (!g_tracking.mysh->hist)
		return (hist_free());
	while (g_tracking.mysh->hist->next)
		g_tracking.mysh->hist = g_tracking.mysh->hist->next;
	tmp = g_tracking.mysh->hist;
	if (hist && !(g_tracking.mysh->hist->previous))
		return (hist_free());
	else
	{
		hist = hist->previous;
		tmp->index = 0;
		free(tmp->line);
		// free(tmp);
		hist = hist_remap_index(hist);
		hist->next = NULL;
	}
	return (hist);
}
