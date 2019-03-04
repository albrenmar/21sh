/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/01 04:18:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void		free_keyval(t_lstcontainer *list)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (list)
	{
		tmp = ft_lstgetfirst(list->firstelement);
		while (tmp)
		{
			buf = tmp->content;
			if (buf)
			{
				free_and_null(buf->key);
				free_and_null(buf->value);
			}
			tmp = tmp->next;
		}
		ft_lstdel(list->firstelement, 1);
		free(list);
		list = NULL;
	}
}

void		clean_up_leaks(void)
{
	if (g_tracking.aut)
		clean_up_autoc();
	if (g_tracking.mysh->alias_lst)
	{
		free_keyval(g_tracking.mysh->alias_lst);
		g_tracking.mysh->alias_lst = NULL;
	}
	ctrl_c();
}

int			ft_exit(void)
{
	if (!g_tracking.jobs->next)
	{
		clean_up_leaks();
		clean_up_leaks();
		ft_putendl("Exit");
		exit(0);
	}
	else
		ft_putendl("There are still jobs running you idiot!");
	return (1);
}