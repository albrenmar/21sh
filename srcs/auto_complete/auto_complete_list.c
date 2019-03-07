/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 01:13:03 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/03/01 06:32:05 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

<<<<<<< HEAD
t_lstcontainer		*change_dir(void)
=======
t_lstcontainer	*change_dir(void)
>>>>>>> alsomvil
{
	if (g_tracking.aut->path != NULL)
	{
		g_tracking.aut->path = ft_strjoinfree("./", g_tracking.aut->path, 2);
		return (build_ls());
	}
	return (NULL);
}

<<<<<<< HEAD
void				print_list2(t_lstcontainer *list)
{
	t_ls			*tmp;
	t_list			*buf;
	int				i;
=======
void	print_list2(t_lstcontainer *list)
{
	t_ls		*tmp;
	t_list		*buf;
	int			i;
>>>>>>> alsomvil

	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		ft_putendl(tmp->name);
		buf = buf->next;
	}
}

<<<<<<< HEAD
void				check_for_escape(void)
=======
void			check_for_escape()
>>>>>>> alsomvil
{
	t_lstcontainer	*new;
	t_list			*buf;
	char			*path;

	new = ft_strsplitlst(g_tracking.aut->path, '\\');
	if (lstcontainer_size(new) > 1)
	{
		buf = new->firstelement;
		path = ft_strnew(0);
		while (buf)
		{
			path = ft_strjoinfree(path, buf->content, 1);
			buf = buf->next;
		}
<<<<<<< HEAD
		free(g_tracking.aut->path);
=======
		free (g_tracking.aut->path);
>>>>>>> alsomvil
		g_tracking.aut->path = path;
	}
	ft_freesplitlist(new);
}

<<<<<<< HEAD
t_lstcontainer		*build_ls(void)
=======
t_lstcontainer	*build_ls(void)
>>>>>>> alsomvil
{
	t_lstcontainer	*liste;
	char			**taab;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = NULL;
	if (g_tracking.aut->path == NULL)
		liste = modified_ls(1, taab);
	else
	{
		check_for_escape();
		taab[1] = g_tracking.aut->path;
		liste = modified_ls(2, taab);
	}
	free(taab);
	return (liste);
}

<<<<<<< HEAD
void				build_comp(t_lstcontainer *list)
{
	t_ls			*tmp;
	t_list			*buf;
	int				i;
=======
void	build_comp(t_lstcontainer *list)
{
	t_ls		*tmp;
	t_list		*buf;
	int			i;
>>>>>>> alsomvil

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
<<<<<<< HEAD
}
=======
}
>>>>>>> alsomvil
