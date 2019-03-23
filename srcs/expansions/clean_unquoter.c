/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_unquoter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 07:35:27 by mjose             #+#    #+#             */
/*   Updated: 2019/03/23 09:13:22 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	clean_unquoter(t_unquoter *unq)
{
	while (unq)
	{
		if (unq->str_unquoted)
			ft_strdel(&unq->str_unquoted);
		ft_memdel((void **)unq);
		unq = unq->next;
	}
	ft_memdel((void **)unq);
}
