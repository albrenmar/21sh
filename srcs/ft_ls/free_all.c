/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:01:42 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/02 06:55:26 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_lstcontainer	*free_all(t_lstcontainer *mainliste, char *dossier)
{
	if (!mainliste)
		return (NULL);
	if (mainliste->firstelement != NULL)
	{
		ft_freestruct(mainliste->firstelement);
		ft_lstdel(mainliste->firstelement, 1);
	}
	ft_free(mainliste);
	ft_free(dossier);
	return (NULL);
}

void			ft_freestructlite(t_ls *tmp)
{
	ft_free(tmp->name);
	ft_free(tmp->strlink);
	ft_free(tmp->path);
	ft_free(tmp->strusrname);
	ft_free(tmp->strgroup);
	ft_free(tmp->strsize);
	ft_free(tmp->strmaj);
	ft_free(tmp->strmin);
	ft_free(tmp->strtime);
	ft_free(tmp->strpermission);
	ft_free(tmp->symlink);
	ft_free(tmp);
}
