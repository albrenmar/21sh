/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 02:42:58 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int					end_word(int mode)
{
	char	*tmp;
	int		i;

	i = utf_goto(g_tracking.str, g_tracking.pos->abs);
	tmp = g_tracking.str;
	mode = 0;
	if (tmp != NULL)
	{
		if (is_space_ac(tmp, i) == 1)
			i--;
		if (is_space_ac(tmp, i) == 1 && (tmp[i] - 1) && tmp[i - 1] == '/')
			return (i + 1);
		while (is_space_ac(tmp, i) != 1 && tmp[i])
			i++;
		print_and_go(i);
	}
	return (i);
}

t_ls				*ls_alloc(char *str)
{
	t_ls			*info;

	info = ft_malloc(sizeof(t_ls) + 1);
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

void				build_var_lst(void)
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
}
