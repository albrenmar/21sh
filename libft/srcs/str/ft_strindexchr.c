/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindexchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:22:02 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:22:02 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strindexchr(const char *str, char search)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == search)
			return (i);
		i++;
	}
	return (0);
}
