/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertpourcent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:30:07 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:29:22 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convertpourcent(t_save *save)
{
	int		temp;

	temp = 0;
	if (save->neg == 1)
		ft_putchar_return('%', save);
	if (save->largeur > 0)
	{
		temp = save->largeur;
		while (temp > 1)
		{
			if (save->zero == 0)
				ft_putchar_return(' ', save);
			else
				ft_putchar_return('0', save);
			temp--;
		}
	}
	if (save->neg == 0)
		ft_putchar_return('%', save);
}
