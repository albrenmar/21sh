/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:38 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:31:32 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*ft_delete(t_env *lst, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	if (!lst)
		return (lst);
	prev = lst;
	if (ft_strcmp(prev->name, name) == 0)
	{
		lst = prev->next;
		free_link(prev);
		return (lst);
	}
	tmp = prev->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			prev->next = tmp->next;
			free_link(tmp);
			return (lst);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (lst);
}
