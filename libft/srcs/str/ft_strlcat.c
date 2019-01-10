/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:22:19 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:22:20 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		ldst;
	size_t		lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	i = 0;
	if (size <= ldst)
		return (size + lsrc);
	while (src[i] && i < (size - ldst - 1))
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[ldst + i] = '\0';
	return (ldst + lsrc);
}
