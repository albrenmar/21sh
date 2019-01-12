/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/12 03:38:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_list(void)
{
	t_ls		*tmp;
	t_list		*buf;
	t_lstcontainer	*list;
	int			i;

	list = g_tracking.aut->comp_list;
	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		ft_putendl(tmp->name);
		buf = buf->next;
	}
}

void	print_list2(t_lstcontainer *list)
{
	t_ls		*tmp;
	t_list		*buf;
	int			i;

	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		ft_putendl(tmp->name);
		buf = buf->next;
	}
}


t_lstcontainer	*build_ls(void)
{
	t_lstcontainer	*liste;
	char			**taab;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = g_tracking.aut->path;
	if (g_tracking.aut->path == NULL)
		liste = modified_ls(1, taab);
	else
		liste = modified_ls(2, taab);
	free(taab);
	return (liste);
}

void	build_comp(t_lstcontainer *list)
{
	t_ls		*tmp;
	t_list		*buf;
	int			i;

	i = ft_strlen(g_tracking.aut->word);
	g_tracking.aut->comp_list = lstcontainer_new();
	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (i != 0)
		{
			if (ft_strncmplc(tmp->name, g_tracking.aut->word, i) == 0)
				lstcontainer_add(g_tracking.aut->comp_list, tmp);
		}
		else
			lstcontainer_add(g_tracking.aut->comp_list, tmp);
		buf = buf->next;
	}
	if (i != 0)
		g_tracking.aut->to_free = list;
}