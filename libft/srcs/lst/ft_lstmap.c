/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:18:43 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:18:45 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list		*begin_list;
	t_list		*temp;
	t_list		*new_list;

	temp = f(lst);
	if (!lst || !f)
		return (NULL);
	if (!(new_list = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	begin_list = new_list;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(new_list->next = ft_lstnew(temp->content, temp->content_size)))
			return (NULL);
		new_list = new_list->next;
		lst = lst->next;
	}
	return (begin_list);
}
