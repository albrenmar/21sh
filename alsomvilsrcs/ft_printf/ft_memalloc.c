/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 23:41:59 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 20:30:41 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memalloc(size_t size)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * size)))
		return (NULL);
	while (size > 0)
	{
		str[size - 1] = '\0';
		size--;
	}
	return (str);
}
