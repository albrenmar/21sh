/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:02:27 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/07 18:21:36 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save history into ~.shell_history
void		hist_save_file(t_hist *hist)
{
	int fd;
	char **line;

	fd = open("/goinfre/.shell_history", O_WRONLY | O_CREAT  | O_TRUNC, 00777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return;
	}
	if (!hist)
	{
		close(fd);
		return;
	}
	while (hist->previous)
		hist = hist->previous;
	while(hist)
	{
		ft_putendl_fd(hist->line, fd);
		if (hist->next)
			hist = hist->next;
		else
			break;
	}
	lseek(fd, SEEK_SET, 0);
	line = malloc(sizeof(line));
	while(get_next_line(fd, line) == 1)
		ft_putendl(*line);
	free(line);
	close(fd);

}

// Remap, reorganize all of the index
t_hist		*hist_remap_index(t_hist *hist)
{
	int i;

	i = 1;
	while (hist->previous)
		hist = hist->previous;
	while (hist)
	{
		hist->index = i;
		i++;
		if (hist->next)
			hist = hist->next;
		else
			break;
	}
	return (hist);
}

// Delete history line sotred at the index
t_hist		*hist_delete_index(t_hist *hist, int index)
{
	t_hist	*tmp;

	if (index <= 0)
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
	if (hist->index == index)
	{
		if (!(hist->previous) && !(hist->next))
			return (hist = hist_free(hist));
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

	if (!hist)
		return hist_free(hist);
	while(hist->next)
		hist = hist->next;
	tmp = hist;
	if (hist && !(hist->previous))
		return hist_free(hist);
	else
	{
		hist = hist->previous;
		free(tmp);
		tmp = 0;
		hist->next = 0;
		hist = hist_remap_index(hist);
	}
	return hist;
}