/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/15 03:28:06 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <errno.h>

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
		ft_strdel(&path);
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
	ft_free(path);
	close(fd);
}

t_hist		*hist_remap_null(t_hist *hist, char *line)
{
	t_hist	*tmp;

	if (!hist || !line || !hist->previous)
		return (NULL);
	while (hist->previous)
		hist = hist->previous;
	if (hist->line == NULL && hist->index == 0\
	&& hist->next && hist->next->line)
	{
		tmp = hist;
		hist = hist->next;
		ft_free(tmp->line);
		ft_free(tmp);
		hist->previous = NULL;
		tmp = NULL;
		g_tracking.hist_first++;
	}
	return (hist);
}

void		hist_lst_add_next(t_hist *hist, char *line)
{
	t_hist	*new_node;

	if (!hist)
	{
		g_tracking.mysh->hist = hist_lst_create(NULL);
		hist = g_tracking.mysh->hist;
	}
	while (hist->next)
		hist = hist->next;
	if (line)
	{
		new_node = ft_memalloc(sizeof(*new_node));
		new_node->index = hist->index + 1;
		new_node->line = ft_strdup_nocar(line);
		new_node->next = NULL;
		new_node->previous = hist;
		hist->next = new_node;
		g_tracking.histmax = new_node->index;
		line = NULL;
	}
}

t_hist		*hist_lst_create(char *line)
{
	t_hist	*new_lst;
	t_hist	*hist;

	hist = g_tracking.mysh->hist;
	if ((new_lst = ft_malloc(sizeof(*new_lst))) == NULL)
		return (NULL);
	if (!line)
		new_lst->index = 0;
	else
		new_lst->index = 1;
	new_lst->line = line;
	new_lst->next = NULL;
	new_lst->previous = NULL;
	return (new_lst);
}

t_hist		*hist_free(void)
{
	t_hist *tmp;

	if (g_tracking.mysh->hist)
	{
		while (g_tracking.mysh->hist->next)
			g_tracking.mysh->hist = g_tracking.mysh->hist->next;
		while (g_tracking.mysh->hist)
		{
			tmp = g_tracking.mysh->hist;
			g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
			ft_free(tmp->line);
			tmp->line = NULL;
			ft_free(tmp);
			tmp = NULL;
		}
	}
	g_tracking.mysh->hist = NULL;
	return (g_tracking.mysh->hist);
}
