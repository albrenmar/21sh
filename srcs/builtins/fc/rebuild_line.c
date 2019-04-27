/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:56:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/27 20:01:59 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*rebuild_line(t_lstcontainer *list)
{
	char	*new;
	t_list	*tmp;

	if (!list)
		return (NULL);
	tmp = ft_lstgetfirst(list->firstelement);
	new = NULL;
	while (tmp)
	{
		new = ft_strjoinfree(new, tmp->content, 1);
		tmp = tmp->next;
	}
	ft_freesplitlist(list);
	return (new);
}