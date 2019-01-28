/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/19 01:13:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_easyprint(t_list *liste)
{
	t_list	*buf;
	t_ls	*tmp;

	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		ft_putendl(tmp->name);
		ft_putcolor(12);
		buf = buf->next;
	}
	return (0);
}

t_lstcontainer	*build_ls(t_auto *aut)
{
	t_lstcontainer	*liste;
	char			**taab;

	taab = malloc(sizeof(char *) * 3);
	taab[0] = "ls";
	taab[1] = aut->path;
	if (aut->path == NULL)
		liste = modified_ls(1, taab);
	else
		liste = modified_ls(2, taab);
	return (liste);
}

void	build_comp(t_lstcontainer *list, t_auto *aut)
{
	t_ls		*tmp;
	t_list		*buf;
	int			i;


	i = ft_strlen(aut->word);
	aut->comp_list = lstcontainer_new();
	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (ft_strncmp(tmp->name, aut->word, i) == 0)
		{
			lstcontainer_add(aut->comp_list, ft_strdup(tmp->name));
			ft_putendl(tmp->name);
		}
		buf = buf->next;
	}
}