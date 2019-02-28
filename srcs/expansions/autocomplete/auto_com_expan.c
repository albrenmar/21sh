/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_com_expan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 03:46:47 by mjose             #+#    #+#             */
/*   Updated: 2019/02/28 04:06:45 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_exp_complete(char *arg)
{
	char	*tmp;

	if (arg)
	{
		tmp = ft_strdup(arg);
		expand_transformer(&tmp);
		return (tmp);
	}
	return (NULL);
}
