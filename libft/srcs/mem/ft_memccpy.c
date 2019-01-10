/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:19:03 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:19:05 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		if ((*p_dst++ = *p_src++) == (unsigned char)c)
			return (p_dst);
		i++;
	}
	return (NULL);
}
