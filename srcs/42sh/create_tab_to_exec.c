/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 02:44:32 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**expand_first_arg(char **tab_exec, int i, int *j, char **tab_farg)
{
	int		i_arg;

	i_arg = 0;
	tab_farg = ft_split_whitespaces(tab_exec[0]);
	if (tab_farg)
		while (tab_farg[i_arg])
			i_arg++;
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
		*j = i_arg;
		free_tab(tab_farg);
	}
	else
		*j = 1;
	return (tab_exec);
}

char	**prepare_tab_to_expand(char **tab_exec, int *j, t_last *begin)
{
	int		i_arg;
	int		i;
	char	**tab_farg;

	i_arg = 0;
	tab_farg = NULL;
	g_tracking.mysh->in_ast = 0;
	g_tracking.mysh->err_expend = 0;
	i = *j;
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	tab_exec[0] = ft_strdup(begin->name);
	expand_transformer(&tab_exec[0], 1);
	expand_first_arg(tab_exec, i, j, tab_farg);
	return (tab_exec);
}

char	*assign_str(t_last *begin)
{
	char	*str;

	str = NULL;
	if (begin->type == OPT || begin->type == ARG)
	{
		str = ft_strdup(begin->name);
		expand_transformer(&str, 1);
	}
	return (str);
}

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	char		**tab_exec;
	int			i;

	begin = list;
	tab_exec = NULL;
	i = 1;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	tab_exec = prepare_tab_to_expand(tab_exec, &i, begin);
	begin = begin->next;
	while (begin && begin->type != CMD)
	{
		if ((tab_exec[i] = assign_str(begin)))
			i++;
		begin = begin->next;
	}
	tab_exec[i] = NULL;
	g_tracking.mysh->in_ast = 1;
	return (tab_exec);
}
