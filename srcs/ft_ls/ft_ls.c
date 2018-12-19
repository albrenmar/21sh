/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:41:15 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/19 01:01:22 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_handlelink(t_list *list, char *dossier, int *flag)
{
	t_ls	*info;
	char	*perm;
	int		i;

	if (list != NULL)
	{
		info = list->content;
		perm = ft_usrmode(info->permission);
		i = ft_strlen(dossier) - 1;
		if (perm[0] == 'l' && dossier[i] != '/')
		{
			info->issimple = 1;
			*flag = 1;
		}
		free(perm);
	}
}

void	get_and_sort(t_lstcontainer *mainliste, char *option)
{
	ft_sort(mainliste->firstelement, option);
	ft_strinfo(mainliste->firstelement);
}

void	ft_folderlist(t_lstcontainer **mainliste, DIR *dir,
char *dossier, char *option)
{
	free_all(*mainliste, NULL);
	*mainliste = lstcontainer_new();
	*mainliste = makelist(*mainliste, dir, dossier, option);
}

t_lstcontainer	*ft_ls(char *name, char *option, int called)
{
	t_lstcontainer		*mainliste;
	DIR					*dir;
	int					flag;
	char				*dossier;

	flag = 0;
	dossier = ft_strdup(name);
	dir = chkdir(dossier, &flag);
	if (dir == NULL)
		return (NULL);
	mainliste = simpleinfo(dossier, option);
	if (ft_edgecase(dossier) == 1)
		return (free_all(mainliste, dossier));
	if (dir == NULL && flag == 0)
		return (free_all(mainliste, dossier));
	if (flag != 1 && checkoption(option, 'd') != 1)
		ft_folderlist(&mainliste, dir, dossier, option);
	if (dir != NULL)
		closedir(dir);
	if (mainliste->firstelement == NULL)
		return (free_all(mainliste, dossier));
	if (needstat(option) == 1)
		get_and_sort(mainliste, option);
	return (mainliste);
}
