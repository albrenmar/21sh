/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyoptiond.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:47:26 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 05:04:31 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_applyoptionx_three(char *str, t_save *save, int *size)
{
	if (save->conversion == 'x')
		ft_putstr_minu(str, save, 0);
	else if (save->conversion == 'X')
		ft_putstr_minu(str, save, 1);
	if (save->neg == 1)
	{
		save->i = 0;
		if (save->precision > 0)
			while (save->i++ < (save->largeur - save->precision))
				ft_putchar_return(' ', save);
		else
			while (save->i++ < (save->largeur - *size))
				ft_putchar_return(' ', save);
	}
}

void	ft_applyoptionx_two(char *str, t_save *save, int *size)
{
	if (save->precision > 0 && save->precision > *size
			&& save->dieze == 0)
		while (save->i++ < (save->precision - *size))
			ft_putchar_return('0', save);
	if (save->dieze == 1 && save->conversion == 'x')
		ft_putstr_minu("0x", save, 0);
	else if (save->dieze == 1 && save->conversion == 'X')
		ft_putstr_minu("0x", save, 1);
	save->i = 0;
	if ((save->largeur > 0 && save->largeur > *size && save->dieze == 1)
			|| (save->largeur == 0 && save->dieze == 1))
		while (save->i++ < (save->precision - (*size - 2))
				&& (save->precision != 0))
			ft_putchar_return('0', save);
	if (save->dieze == 1 && save->largeur > 0)
	{
		if (save->zero == 1 && save->precisionnull == 0)
			while (save->i++ < (save->largeur - (*size - 1)) && save->neg == 0)
				ft_putchar_return('0', save);
	}
	ft_applyoptionx_three(str, save, size);
}

void	ft_applyoptionx_one(char *str, t_save *save, int *size)
{
	if (save->largeur > 0 && save->largeur > *size && save->dieze == 0
			&& save->precision > *size && save->neg == 0)
	{
		while (save->i++ < (save->largeur - save->precision))
			ft_putchar_return(' ', save);
		save->i = 0;
		while (save->i++ < (save->precision - *size))
			ft_putchar_return('0', save);
	}
	if (save->largeur > 0 && save->largeur > *size
			&& save->dieze == 1 && save->zero == 0 && save->precision == 0)
	{
		while (save->i++ < (save->largeur - *size))
			ft_putchar_return(' ', save);
	}
	else if (save->largeur > 0 && save->largeur > *size
			&& save->dieze == 1 && save->zero == 1 && save->precisionnull == 1)
	{
		while (save->i++ < (save->largeur - *size))
			ft_putchar_return(' ', save);
	}
	ft_applyoptionx_two(str, save, size);
}

void	ft_applyoptionx(char *str, t_save *save)
{
	int		size;

	size = ft_strlen(str);
	if (save->precisionnull == 1 && ft_atoi(str) == 0 && save->largeur != 0)
	{
		while (save->i++ < save->largeur)
			ft_putchar_return(' ', save);
		return ;
	}
	if (save->dieze)
		size = size + 2;
	if (save->neg == 1)
		while (save->i++ < (save->precision - size))
			ft_putchar_return('0', save);
	if (save->largeur > 0 && save->largeur > size && save->dieze == 0
			&& save->precision < size)
		while (save->i++ < (save->largeur - size))
		{
			if ((save->zero == 0 && save->neg == 0) || (save->zero == 1
						&& save->precision <= size && save->precision > 0))
				ft_putchar_return(' ', save);
			else if (save->zero == 1)
				ft_putchar_return('0', save);
		}
	ft_applyoptionx_one(str, save, &size);
}
