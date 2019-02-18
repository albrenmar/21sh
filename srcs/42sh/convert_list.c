/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_list_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 07:07:00 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/17 06:16:25 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

t_last		*new_list(void)
{
	t_last		*new;

	new = ft_memalloc(sizeof(t_last));
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		at_end_list(t_last *new, t_last *list)
{
	t_last		*temp;

	temp = new;
	while (new->next)
		new = new->next;
	new->next = new_list();
	new->next->prev = new;
	new = new->next;
	new->name = ft_strdup(list->name);
	new->type = list->type;
	new = temp;
}

char		*add_str(char *new, char *list)
{
	if (new == NULL)
		new = ft_strdup(list);
	else
	{
		new = ft_strjoin(new, " ");
		new = ft_strjoin(new, list);
	}
	return (new);
}

t_last		*convert_list(t_last *list)
{
	t_last	*new;

	new = NULL;
	while (list)
	{
		if (!new)
			new = new_list();
		else
		{
			new->next = new_list();
			new->next->prev = new;
			new = new->next;
		}
		new->type = list->type;
		if (list->type == DESCR || list->type == OP)
		{
			new->name = ft_strdup(list->name);
			list = list->next;
		}
		else
		{
			while (list && list->type != DESCR && list->type != OP)
			{
				new->name = add_str(new->name, list->name);
				list = list->next;
			}
		}
	}
	while (new->prev)
		new = new->prev;
	return (new);
}
