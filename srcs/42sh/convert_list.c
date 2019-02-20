/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_list_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 07:07:00 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 10:26:47 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define PREV list->prev_wihtout_descr
#define LIST list->type

t_last		*new_list(void)
{
	t_last		*new;

	new = ft_memalloc(sizeof(t_last));
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->prev_wihtout_descr = NULL;
	return (new);
}

void		convert_list(t_last *list)
{
	t_last	*begin;

	begin = list;
	while (list)
	{
		if (list->type == DESCR)
			;
		else if (!its_reddir(list) && !its_fd_reddir(list) && (!PREV || (PREV && (its_pipe(PREV) || PREV->type == SEP))))
			LIST = CMD;
		else if (its_pipe(list) || its_reddir(list) || its_fd_reddir(list))
			LIST = OP;
		else if (its_separator(list))
			LIST = SEP;
		else if (PREV && (its_reddir(PREV) || its_fd_reddir(PREV)))
				LIST = FICH;
		else if (list->name[0] == '-')
		{
			if ((PREV && (PREV->type == CMD || PREV->type == FICH || PREV->type == OPT)))
				LIST = OPT;
			else if (PREV && PREV->type == ARG)
				LIST = ARG;
		}
		else if (PREV && (PREV->type == FICH || PREV->type == OPT || PREV->type == ARG))
			LIST = ARG;
		else if (its_pipe(list) || its_reddir(list) || its_fd_reddir(list))
			LIST = OP;
		else if (LIST != SEP && LIST != OP && (PREV && (PREV->type == OPT || PREV->type == CMD)))
			LIST = ARG;
		list = list->next;
	}
	list = begin;
}
