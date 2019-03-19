/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/19 15:37:31 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

void		hist_setup_file(void)
{
	int		fd;
	char	**line;

	line = ft_memalloc(sizeof(line));
	fd = open("/goinfre/.shell_history", O_CREAT | O_APPEND | O_RDWR, 00777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return ;
	}
	if (get_next_line(fd, line) == 1)
	{
		g_tracking.mysh->hist = hist_lst_create(*line);
		while (get_next_line(fd, line) == 1 && *line != NULL)
			hist_lst_add_next(g_tracking.mysh->hist, *line);
	}
	close(fd);
	free(line);
}

void		hist_lst_add_next(t_hist *hist, char *line)
{
	t_hist	*new_node;
	if (!hist || (!hist && !hist->line))
		g_tracking.mysh->hist = hist_lst_create(line);
	while (hist->next != NULL)
		hist = hist->next;
	new_node = ft_memalloc(sizeof(*new_node));
	new_node->index = hist->index + 1;
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	new_node->previous = hist;
	hist->next = new_node;
	g_tracking.histmax = new_node->index;
	line = NULL;
}

void		hist_print(t_hist *hist)
{
	while (hist && hist->previous)
		hist = hist->previous;
	while (hist && hist->line)
	{
		ft_putnbr(hist->index);
		ft_putchar(' ');
		ft_putendl(hist->line);
		if (hist->next)
			hist = hist->next;
		else
			break ;
	}
}

t_hist		*hist_lst_create(char *line)
{
	t_hist	*new_lst;

	new_lst = malloc(sizeof(*new_lst));
	new_lst->index = 1;
	new_lst->line = line;
	new_lst->next = NULL;
	new_lst->previous = NULL;
	return (new_lst);
}

t_hist		*hist_free(t_hist *hist)
{
	t_hist *tmp;

	if (hist)
	{
		while (hist->next)
			hist = hist->next;
		while (hist)
		{
			tmp = hist;
			hist = hist->previous;
			free(tmp->line);
			free(tmp);
		}
	}
	return (hist);
}
