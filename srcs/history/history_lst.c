/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/10 14:49:43 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Add node at the end
void		hist_lst_add_next(t_core *core)
{
	t_hist	*new_node;

	while (core->hist->next != NULL)
		core->hist = core->hist->next;
	new_node = ft_memalloc(sizeof(*new_node));
	new_node->index = core->hist->index + 1;
	new_node->line = ft_strdup(core->line);
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
	new_lst->index = 0;
	new_lst->line = ft_strdup(core->line);
	new_lst->next = NULL;
	new_lst->previous = NULL;

	return (new_lst);
}