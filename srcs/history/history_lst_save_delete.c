/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_save_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:32:39 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/28 15:55:50 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		hist_save_file(t_hist *hist)
{
	int		fd;
	char	*path;

	path = create_path_hist();
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 00777);
	if (fd < 0)
		return (ft_putendl_fd("Error while opening/creating .42hist", 2));
	if (!hist)
	{
		close(fd);
		return ;
	}
	while (hist->previous)
		hist = hist->previous;
	while (hist)
	{
		if (hist->line != NULL && ft_strlen(hist->line) > 0)
			ft_putendl_fd(hist->line, fd);
		hist = hist->next;
	}
	free(path);
	close(fd);
}

int			delete_index_special_neg(void)
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
		free(tmp->line);
		free(tmp);
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

int			delete_index_neg(int index)
{
	t_hist	*tmp;
	t_hist	*tmpo;

	tmpo = g_tracking.mysh->hist;
	while (tmpo->next)
		tmpo = tmpo->next;
	if ((tmp->index - index) == g_tracking.mysh->hist->index)
		if (g_tracking.mysh->hist)
		{
			if (delete_index_special_neg())
				return (1);
			if (g_tracking.mysh->hist->previous && g_tracking.mysh->hist->next)
			{
				tmp = g_tracking.mysh->hist;
				g_tracking.mysh->hist->previous->next =\
				g_tracking.mysh->hist->next;
				g_tracking.mysh->hist->next->previous =\
				g_tracking.mysh->hist->previous;
				free(tmp->line);
				free(tmp);
				g_tracking.mysh->hist = hist_remap_index(g_tracking.mysh->hist);
				return (1);
			}
		}
	return (0);
}

int			delete_index_dispatch(int index)
{
	if (ft_atoi(g_tracking.g_tab_exec[2]) > 0)
	{
		if ((index = search_index_to_delete(ft_atoi(g_tracking.g_tab_exec[2])))\
		== 0)
			return (0);
		if (delete_index(index) == 0)
			return (0);
	}
	if (ft_atoi(g_tracking.g_tab_exec[2]) < 0)
	{
		if ((index = search_index_to_delete_neg(\
		ft_atoi(g_tracking.g_tab_exec[2]))) == 0)
			return (0);
		if (delete_index_neg(index) == 0)
			return (0);
	}
	return (1);
}
