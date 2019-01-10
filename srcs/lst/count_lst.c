/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:28 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:31:28 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_count_list(t_env *env)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = env;
	if (!env)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
