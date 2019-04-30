/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/04/30 21:12:06 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**convert_backtab(char **taab)
{
	int		i;

	i = 0;
	while (taab[i])
	{
		taab[i] = convert_back(taab[i]);
		taab[i] = remove_back(taab[i]);
		i++;
	}
	return (taab);
}
