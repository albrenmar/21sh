/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/19 01:10:49 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	asign_word(t_auto *aut)
{
	t_lstcontainer		*tmp;
	t_list				*buf;

	if (ft_strlen(g_tracking.str) != 0)
	{
		tmp = ft_strsplitlst(g_tracking.str, ' ');
		buf = ft_lstgetlast(tmp->firstelement);
		aut->word = ft_strdup(buf->content);
		ft_freesplitlist(tmp);
	}
	else
		aut->word = NULL;
}

int		check_if_path(t_auto *aut)
{
	t_lstcontainer	*tmp;
	t_list			*buf;
	char			*path;
	int				i;

	aut->path = NULL;
	if (aut->word[0] == '/')
		aut->path = ft_strdup(aut->word);
	tmp = ft_strsplitlst(aut->word, '/');
	i = lstcontainer_size(tmp);
	if (i > 1)
	{
		path = ft_strnew(0);
		buf = tmp->firstelement;
		while (buf->next != NULL)
		{
			path = ft_strjoinfree("/", path, 2);
			path = ft_strjoinfree(path, buf->content, 1);
			path = ft_strjoinfree(path, "/", 1);
			buf = buf->next;
		}
		ft_freesplitlist(tmp);
		free(aut->path);
		aut->path = path;
		return (1);
	}
	return (0);
}

void	build_list(t_auto *aut)
{
	t_lstcontainer	*list;

	if (aut->word)
	{
		check_if_path(aut);
		list = build_ls(aut);
		if (list != NULL)
			build_comp(list, aut);
	}
	ft_lstdel(list->firstelement, 1);
	free(list);
}


int		auto_complete(void)
{
	t_auto			*aut;

	if (!(aut = malloc(sizeof(t_auto))))
		return (1);
	asign_word(aut);
	build_list(aut);
	return (0);
}