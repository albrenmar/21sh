/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/11 16:04:30 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// Get all the entry from the file of history If it does not exist, it is created
void		hist_setup_file(t_core *core)
{
	int fd;
	char **line;

	line = ft_memalloc(sizeof(line));
	// FD DONT WORKKK
	fd = open("/goinfre/.shell_history", O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return;
	}
	if (core->hist == NULL && core->line)
		core->hist = hist_lst_create(core);
	while (get_next_line(fd, line) == 1 && *line != NULL)
		hist_lst_add_next(core, *line);
	close(fd);
	free(line);
}

// Add node at the end
void		hist_lst_add_next(t_core *core,char *line)
{
	t_hist	*new_node;

	while (core->hist->next != NULL)
		core->hist = core->hist->next;
	new_node = ft_memalloc(sizeof(*new_node));
	new_node->index = core->hist->index + 1;
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	new_node->previous = core->hist;
	core->hist->next = new_node;
}

// Print history list
void		hist_print(t_core *core)
{
	while(core->hist->previous)
		core->hist = core->hist->previous;
	
	while (core->hist)
	{
		ft_putendl(core->hist->line);
		if (core->hist->next)
			core->hist = core->hist->next;
		else
			break;
	}
}
// Create a new list
t_hist		*hist_lst_create(t_core *core)
{
	t_hist	*new_lst;

	new_lst = malloc(sizeof(*new_lst));
	new_lst->index = 1;
	new_lst->line = ft_strdup(core->line);
	new_lst->next = NULL;
	new_lst->previous = NULL;

	return (new_lst);
}
// free/clear the history
void		hist_free(t_core *core)
{
	t_hist *tmp;
	while (core->hist->previous)
		core->hist = core->hist->previous;
	while(core->hist)
	{
		tmp = core->hist;
		core->hist = core->hist->next;
		free(tmp);
	}
}