/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/15 23:10:33 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	char		**tab_exec;
	int			i;

	begin = list;
	i = 0;
	i++;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	list = begin;
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	tab_exec[i] = list->name;
	list = list->next;
	i++;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
		{
			tab_exec[i] = list->name;
			i++;
		}
		list = list->next;
	}
	if (tab_exec)
		tab_exec[i] = NULL;
	return (tab_exec);
}
