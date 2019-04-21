/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by mjose             #+#    #+#             */
/*   Updated: 2019/04/21 22:06:01 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	char		**tab_exec;
	char		**tab_farg;
	int			i;
	int			i_arg;

	begin = list;
	g_tracking.mysh->in_ast = 0;
	i = 1;
	i_arg = 0;
	g_tracking.mysh->err_expend = 0;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	tab_exec[0] = ft_strdup(begin->name);
	expand_transformer(&tab_exec[0], 1);
	tab_farg = ft_split_whitespaces(tab_exec[0]);
	if (tab_farg)
	{
		i_arg = 0;
		while (tab_farg[i_arg])
			i_arg++;
	}
	if (i_arg > 1)
	{
		free_tab(tab_exec);
		tab_exec = ft_memalloc(sizeof(char *) * (i + i_arg + 1));
		i_arg = 0;
		while (tab_farg[i_arg])
		{
			tab_exec[i_arg] = ft_strdup(tab_farg[i_arg]);
			i_arg++;
		}
		i = i_arg;
		free_tab(tab_farg);
	}
	else
		i = 1;
	begin = begin->next;
//	i = 1;
	while (begin && begin->type != CMD)
	{
		if (begin->type == OPT || begin->type == ARG)
		{
			tab_exec[i] = ft_strdup(begin->name);
			expand_transformer(&tab_exec[i], 1);
			i++;
		}
		begin = begin->next;
	}
	tab_exec[i] = NULL;
	g_tracking.mysh->in_ast = 1;
	return (tab_exec);
}
