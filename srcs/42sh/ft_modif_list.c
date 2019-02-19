/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:46:30 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/19 06:33:06 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_last	*create_new_list(void)
{
	t_last	*list;

	list = malloc(sizeof(t_last));
	list->name = NULL;
	list->next = NULL;
	list->prev = NULL;
	list->prev_wihtout_descr = NULL;
	return (list);
}

void	rm_pointer(t_last *to_rm)
{
	t_last		*prev;
	t_last		*next;

	prev = to_rm->prev;
	next = to_rm->next;

	if (next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else
		prev->next = NULL;
}

void	add_pointer(t_last	*ref, t_last *to_add)
{
	t_last		*prev;
	t_last		*next;

	prev = ref->prev;
	if (prev)
		prev->next = to_add;
	to_add->prev = prev;
	ref->prev = to_add;
	to_add->next = ref;
}

void	insert_node(t_last *ref_node, t_last *insert)
{
	t_last	*tmp;

	tmp = insert;
	rm_pointer(insert);
	add_pointer(ref_node, insert);
}
