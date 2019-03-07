/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 01:42:43 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/01/23 00:06:50 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

<<<<<<< HEAD
t_ls				*ls_alloc(char *str)
{
	t_ls			*info;
=======
t_ls	*ls_alloc(char	*str)
{
	t_ls	*info;
>>>>>>> alsomvil

	info = malloc(sizeof(t_ls) + 1);
	info->name = ft_strdup(str);
	info->path = NULL;
	info->symlink = NULL;
	info->strusrname = NULL;
	info->strgroup = NULL;
	info->strlink = NULL;
	info->strtime = NULL;
	info->strpermission = ft_strdup("---------");
	info->strsize = NULL;
	info->strmin = NULL;
	info->strmaj = NULL;
	info->strpad = NULL;
	info->timeswitch = 0;
	info->color = 0;
	info->issimple = 1;
	return (info);
}

<<<<<<< HEAD
void				build_var_lst(void)
=======
void	build_var_lst()
>>>>>>> alsomvil
{
	t_list			*buf;
	t_keyval		*tmp;
	t_ls			*new;

	buf = g_tracking.mysh->env->firstelement;
	if (!buf)
		return ;
	g_tracking.aut->var_lst = lstcontainer_new();
	while (buf)
	{
		tmp = buf->content;
		new = ls_alloc(tmp->key);
		lstcontainer_add(g_tracking.aut->var_lst, new);
		buf = buf->next;
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> alsomvil
