/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_com_expan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 03:46:47 by mjose             #+#    #+#             */
/*   Updated: 2019/04/11 04:25:53 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_exp_complete(char *arg)
{
	char	*tmp;

	if (arg)
	{
		tmp = ft_strdup(arg);
		ft_free(arg);
		expand_transformer(&tmp);
		return (tmp);
	}
	return (NULL);
}
