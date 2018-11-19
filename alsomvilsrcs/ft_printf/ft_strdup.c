/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:03:01 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 21:36:58 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)s1;
	while (s1[i++])
		;
	if (!(temp = ft_memalloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = s1[i];
	return (temp);
}
