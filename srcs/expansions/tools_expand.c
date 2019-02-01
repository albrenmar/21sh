/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 01:23:51 by mjose             #+#    #+#             */
/*   Updated: 2019/02/01 05:28:53 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	delete_letter_expand(t_expand **letter)
{
	t_expand	*prev;
	t_expand	*next;

	prev = (*letter)->prev;
	next = (*letter)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(*letter);
	if (next)
		*letter = next;
	else
		*letter = NULL;
}

void	delete_list_expand(t_expand **letter)
{
	t_expand	*next;

	next = NULL;
	while (*letter && (*letter)->next)
	{
		if ((*letter)->next)
			next = (*letter)->next;
		delete_letter_expand(letter);
		if (next)
			*letter = next;
		else
			*letter = NULL;
	}
	*letter = NULL;
}

void	update_list_expand(t_expand **letter, char **str)
{
	t_expand	*new_letter;

	delete_list_expand(letter);
	*letter = NULL;
	new_letter = new_expand(ft_strlen(*str));
	*letter = new_letter;
	create_list_expand(*letter, *str);
}
