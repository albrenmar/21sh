/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:25:47 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:54:51 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convertp_one(t_save *save, char *str, int i, int size)
{
	while (save->i++ < (save->largeur - size))
		ft_putchar_return(' ', save);
	if (save->neg == 0)
	{
		ft_putstr_return("0x", save);
		if (!save->precisionnull && save->precision <= save->largeur)
			ft_putstr_minu(str, save, 0);
		if (save->precision > size - 2)
		{
			while (save->precision > 0 && i < save->precision - (size - 2))
			{
				ft_putchar_return('0', save);
				i++;
			}
		}
		if (!save->precisionnull && save->precision > save->largeur)
			ft_putstr_minu(str, save, 0);
	}
}

void	ft_convertp(va_list test, t_save *save)
{
	void				*arg;
	char				*str;
	unsigned long long	i;
	int					size;

	arg = va_arg(test, void*);
	i = (unsigned long long)arg;
	str = ft_itoabase(i, 16);
	size = ft_strlen(str) + 2;
	i = 0;
	if (save->neg == 1)
	{
		ft_putstr_return("0x", save);
		ft_putstr_minu(str, save, 0);
	}
	ft_convertp_one(save, str, i, size);
	ft_memdel((void **)&str);
}
