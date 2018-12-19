/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:01:42 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:33:22 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer	*free_all(t_lstcontainer *mainliste, char *dossier)
{
	if (mainliste->firstelement != NULL)
	{
		ft_freestruct(mainliste->firstelement);
		ft_lstdel(mainliste->firstelement, 0);
	}
	free(mainliste);
	free(dossier);
	return (NULL);
}

void	ft_freestructlite(t_ls *tmp)
{
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
	free(tmp);
}
