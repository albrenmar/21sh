/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	char		**tab_exec;
	int			i;

	begin = list;
	i = 1;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	tab_exec[0] = ft_strdup(begin->name);
	begin = begin->next;
	i = 1;
	while (begin && begin->type != CMD)
	{
		if (begin->type == OPT || begin->type == ARG)
			tab_exec[i++] = ft_strdup(begin->name);
		begin = begin->next;
	}
	tab_exec[i] = NULL;
	return (tab_exec);
}
