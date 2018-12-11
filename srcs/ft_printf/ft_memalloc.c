/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 23:41:59 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/10 17:39:15 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	nb;

	nb = 0;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (nb < (size + 1))
	{
		str[nb] = '\0';
		nb++;
	}
	return (str);
}
