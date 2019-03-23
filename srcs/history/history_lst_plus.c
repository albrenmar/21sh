/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:02:27 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 14:34:40 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_hist		*hist_remap_index(t_hist *hist)
{
	int i;

	i = 1;
	if (!hist)
		return (NULL);
	while (hist->previous)
		hist = hist->previous;
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

t_hist		*hist_delete_index_setup(t_hist *hist, int index)
{
	if (index < 1)
	{
		ft_putendl_fd("history position out of range", 2);
		return (hist);
	}
	while (hist->index > index)
	{
		if (hist->previous == NULL)
		{
			ft_putendl_fd("history position out of range", 2);
			return (hist);
		}
		hist = hist->previous;
	}
	while (hist->index < index)
	{
		if (hist->next == NULL)
		{
			ft_putendl_fd("history position out of range", 2);
			return (hist);
		}
		hist = hist->next;
	}
	return (NULL);
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

	if (!hist || !hist->line)
		return (NULL);
	if ((hist = hist_delete_index_setup(hist, index)) != NULL)
		return (hist);
	if (hist->index == index)
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
		free(tmp);
		hist = hist_remap_index(hist);
	}
	return (hist);
}
