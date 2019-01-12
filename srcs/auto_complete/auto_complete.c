/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/12 04:52:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	asign_word(void)
{
	t_lstcontainer		*tmp;
	t_list				*buf;
	int					i;
	int					a;

	if (ft_strlen(g_tracking.str) != 0)
	{
		i = utf_goto(g_tracking.str, g_tracking.pos->abs);
		a = i;
		while(g_tracking.str[i] != ' ' && i != 0)
				i--;
		if (g_tracking.str[i] == ' ')
			i++;
		while(g_tracking.str[a] != ' ' && a != ft_strlen(g_tracking.str))
				a++;
		a = a - i;
		if (a != 0)
			g_tracking.aut->word = ft_strsub(g_tracking.str, i, a, 0);
	}
}

t_auto		*init_auto(void)
{
	t_auto		*aut;

	if (!(aut = malloc(sizeof(t_auto))))
		return (NULL);
	aut->word = NULL;
	aut->path = NULL;
	aut->menuline = NULL;
	aut->comp_list = NULL;
	aut->to_free = 0;
	aut->to_add = NULL;
	aut->size = 0;
	aut->col_nbr = 0;
	aut->lin_nbr = 0;
	aut->line_up = 0;
	return (aut);
}

void	build_list(void)
{
	t_lstcontainer	*list;

	list = NULL;
	g_tracking.aut->comp_list = NULL;
	if (g_tracking.aut->word)
	{
		assign_type();
		list = build_ls();
		if (list != NULL)
		{
			build_comp(list);
			g_tracking.aut->to_add = NULL;
			if (g_tracking.aut->comp_list->firstelement != NULL)
			{
				get_max_size();
				rem_str(g_tracking.aut->word);
				set_up_page();
				completion_loop(g_tracking.aut->comp_list->firstelement);
			}
		}
	}
	else
	{
		g_tracking.aut->comp_list = build_ls();
		get_max_size();
		set_up_page();
		completion_loop(g_tracking.aut->comp_list->firstelement);
	}
}

int		auto_complete(void)
{
	if ((g_tracking.aut = init_auto()) == NULL)
		return (1);
	asign_word();
	build_list();
	clean_up_autoc();
	return (0);
}