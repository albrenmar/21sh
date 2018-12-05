/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:49:50 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:40:21 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*temp;

	i = 0;
	if (!(temp = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	temp[i] = '\0';
	return (temp);
}
