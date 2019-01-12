/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 23:41:59 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:37:49 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

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
