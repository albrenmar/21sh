/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_applyoptiond.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:47:26 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:58:57 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pasdeplace(t_save *save, int neg, int *size)
{
	if (save->precision < *size)
	{
		while (save->i++ < (save->largeur - *size))
			ft_putchar_return(' ', save);
	}
	else if (save->pos == 1)
	{
		while (save->i++ < (save->largeur - save->precision - 1))
			ft_putchar_return(' ', save);
		ft_putchar_return('+', save);
	}
	else if (save->pos == 0)
	{
		if (neg == 1)
			save->i++;
		while (save->i++ < (save->largeur - save->precision))
			ft_putchar_return(' ', save);
	}
}

void	ft_applyoptiond_three(t_save *save, int neg, int *size)
{
	if (save->largeur > 0 && save->zero == 1 && save->neg == 0)
	{
		if (save->pos == 1 && save->precision > 0)
			ft_putchar_return('+', save);
		if (save->space == 1)
			save->i++;
		if (save->precision < *size)
		{
			while (save->precision > 0 && save->i < (save->largeur - *size))
			{
				ft_putchar_return(' ', save);
				save->i++;
			}
		}
		else if (save->precision >= *size)
		{
			while (save->i < (save->largeur - save->precision) && neg == 0)
			{
				ft_putchar_return(' ', save);
				save->i++;
			}
		}
		while (save->i++ < (save->largeur - *size) && save->precision == 0)
			ft_putchar_return('0', save);
	}
}

void	ft_applyoptiond_two(char *str, t_save *save, int *size)
{
	if (save->precision > 0)
	{
		save->i = 0;
		while (save->i++ < (save->precision - *size))
			ft_putchar_return('0', save);
	}
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
		{
			while (save->i++ < (save->largeur - *size))
				ft_putchar_return(' ', save);
		}
	}
}

void	ft_applyoptiond_one(char *str, t_save *save, int neg, int *size)
{
	if (save->largeur > 0 && save->zero == 1 && save->pos == 1
			&& save->precision == 0)
	{
		if (save->pos == 1 && neg == 0)
			ft_putchar_return('+', save);
		while (save->i++ < (save->largeur - *size))
			ft_putchar_return('0', save);
	}
	if (save->largeur > 0 && save->zero == 1 && save->pos == 1
			&& save->precision > 0)
	{
		while (save->i++ < (save->largeur - save->precision - 1))
			ft_putchar_return(' ', save);
	}
	ft_applyoptiond_three(save, neg, size);
	if (save->pos == 1 && neg == 0 && save->largeur == 0
			&& save->conversion != 'u')
		ft_putchar_return('+', save);
	if (ft_atoi(str) == 0 && save->precisionnull == 1)
		return ;
	ft_applyoptiond_two(str, save, size);
}

void	ft_applyoptiond(char *str, t_save *save, int neg)
{
	int		size;

	size = ft_strlen(str);
	if (save->precisionnull == 1 && ft_atoi(str) == 0 && save->pos == 0
			&& save->space == 0)
	{
		while (save->i++ < save->largeur)
			ft_putchar_return(' ', save);
		return ;
	}
	if ((neg == 1 || save->pos == 1) && save->precision < size)
		size++;
	if (save->space == 1 && save->neg == 0 && save->precision == 0
			&& neg == 0 && save->pos == 0 && save->conversion != 'u')
		ft_putchar_return(' ', save);
	if (save->largeur > 0 && save->zero == 0 && save->neg == 0)
		ft_pasdeplace(save, neg, &size);
	if (neg == 1)
		ft_putchar_return('-', save);
	if (save->neg == 1 && save->pos == 1)
		ft_putchar_return('+', save);
	ft_applyoptiond_one(str, save, neg, &size);
	ft_memdel((void **)&str);
}
