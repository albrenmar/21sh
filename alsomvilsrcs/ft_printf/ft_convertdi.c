/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 03:36:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:55:18 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convertshort(va_list test, t_save *save)
{
	short	argument;

	if ((save->conversion == 'U' || save->conversion == 'u'))
	{
		if (save->flaghh == 0)
			argument = (unsigned short)va_arg(test, int);
		else
			argument = (unsigned char)va_arg(test, int);
		ft_applyoptiond(ft_itoabase((unsigned short)argument, 10), save, 0);
		return ;
	}
	if (save->conversion != 'u' && save->conversion != 'U' && save->flaghh == 1)
		argument = (char)va_arg(test, int);
	else
		argument = (short)va_arg(test, int);
	if (argument < 0)
		ft_applyoptiond(ft_itoabase(-argument, 10), save, 1);
	else
		ft_applyoptiond(ft_itoabase(argument, 10), save, 0);
}

void	ft_convertlong(va_list test, t_save *save)
{
	long long	argument;

	argument = va_arg(test, long long);
	if ((save->conversion == 'U' || save->conversion == 'u') && argument < 0)
	{
		ft_applyoptiond(ft_itoabase((unsigned long long)argument, 10), save, 0);
		return ;
	}
	if (argument < 0)
		ft_applyoptiond(ft_itoabase(-argument, 10), save, 1);
	else
		ft_applyoptiond(ft_itoabase((unsigned long long)argument, 10), save, 0);
}

void	ft_convertdi_two(va_list test, t_save *save)
{
	intmax_t		temp;

	if (save->flagz == 1)
		temp = (intmax_t)va_arg(test, size_t);
	else if (save->flagj == 1)
		temp = (intmax_t)va_arg(test, intmax_t);
	else
		temp = (intmax_t)va_arg(test, int);
	if (temp < 0)
		ft_applyoptiond(ft_itoabase(-temp, 10), save, 1);
	else
		ft_applyoptiond(ft_itoabase(temp, 10), save, 0);
}

void	ft_convertdi_one(va_list test, t_save *save)
{
	uintmax_t		arg;

	if (save->conversion == 'u')
	{
		if (save->flagz == 1)
			arg = (uintmax_t)va_arg(test, size_t);
		else if (save->flagj == 1)
			arg = (uintmax_t)va_arg(test, uintmax_t);
		else
			arg = (uintmax_t)va_arg(test, unsigned int);
		ft_applyoptiond(ft_itoabase(arg, 10), save, 0);
		return ;
	}
	else
		ft_convertdi_two(test, save);
}

void	ft_convertdi(va_list test, t_save *save)
{
	int				i;

	i = 0;
	if ((save->conversion == 'i' || save->conversion == 'd'
				|| save->conversion == 'u') && !save->flagl && !save->flagll
			&& !save->flagh && !save->flaghh)
		ft_convertdi_one(test, save);
	else if ((save->conversion == 'i' || save->conversion == 'd'
				|| save->conversion == 'u')
			&& (save->flagh || save->flaghh))
		ft_convertshort(test, save);
	else
		ft_convertlong(test, save);
}
