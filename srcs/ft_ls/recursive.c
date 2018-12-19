/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 00:23:13 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:38:02 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			ft_freestruct(t_list *liste)
{
	t_list	*buf;
	t_ls	*tmp;

	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		free(tmp->name);
		free(tmp->strlink);
		free(tmp->path);
		free(tmp->strusrname);
		free(tmp->strgroup);
		free(tmp->strsize);
		free(tmp->strmaj);
		free(tmp->strmin);
		free(tmp->strtime);
		free(tmp->strpermission);
		free(tmp->symlink);
		free(buf->content);
		buf = buf->next;
	}
}