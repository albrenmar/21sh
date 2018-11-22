/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyoptiond.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:47:26 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 05:10:31 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_applyoptiono_three(t_save *save, int *size)
{
	if (save->largeur > 0 && save->zero == 1 && save->neg == 0)
	{
		if (save->pos == 1 && save->precision > 0)
			ft_putchar_return('+', save);
		if (save->space == 1)
			save->i++;
		if (save->precision < *size)
		{
			while ((save->precision > 0 || save->precisionnull == 1)
					&& save->i < (save->largeur - *size))
			{
				ft_putchar_return(' ', save);
				save->i++;
			}
		}
		else if (save->precision >= *size)
		{
			while (save->i++ < (save->largeur - save->precision))
				ft_putchar_return(' ', save);
		}
		while (save->i++ < (save->largeur - *size) && save->precision == 0)
			ft_putchar_return('0', save);
	}
}

void	ft_applyoptiono_two(char *str, t_save *save, int *size)
{
	if (save->dieze == 1 && ft_atoi(str) != 0)
		ft_putchar_return('0', save);
	if (save->dieze == 0 && ft_atoi(str) == 0
			&& save->precisionnull == 1 && save->largeur > 0)
		ft_putchar_return(' ', save);
	else if (save->dieze == 0 && ft_atoi(str) == 0
			&& save->precisionnull == 1 && save->largeur == 0)
		;
	else
		ft_putstr_return(str, save);
	if (save->largeur > 0 && save->neg == 1)
	{
		save->i = 0;
		if (save->precision > *size)
		{
			if (save->pos == 1)
				save->precision++;
			while (save->i++ < (save->largeur - save->precision))
				ft_putchar_return(' ', save);
		}
		else
			while (save->i++ < (save->largeur - *size))
				ft_putchar_return(' ', save);
	}
}

void	ft_applyoptiono_one(char *str, t_save *save, int *size)
{
	if (save->largeur > 0 && save->zero == 1 && save->pos == 1
			&& save->precision > 0)
	{
		while (save->i++ < (save->largeur - save->precision - 1))
			ft_putchar_return(' ', save);
	}
	ft_applyoptiono_three(save, size);
	if (save->precision > 0)
	{
		save->i = 0;
		while (save->i++ < (save->precision - *size))
			ft_putchar_return('0', save);
	}
	ft_applyoptiono_two(str, save, size);
}

void	ft_applyoptiono(char *str, t_save *save, int neg)
{
	int		size;

	size = ft_strlen(str);
	if ((neg == 1 || save->pos == 1) && save->precision < size)
		size++;
	if (save->dieze == 1 && ft_atoi(str) != 0)
		size++;
	if (save->largeur > 0 && save->zero == 0 && save->neg == 0)
		ft_pasdeplace(save, neg, &size);
	if (neg == 1)
		ft_putchar_return('-', save);
	if (save->neg == 1 && save->pos == 1)
		ft_putchar_return('+', save);
	if (save->largeur > 0 && save->zero == 1 && save->pos == 1
			&& save->precision == 0)
	{
		if (save->pos == 1 && neg == 0)
			ft_putchar_return('+', save);
		while (save->i++ < (save->largeur - size))
			ft_putchar_return('0', save);
	}
	ft_applyoptiono_one(str, save, &size);
}
