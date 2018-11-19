/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuni.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:49:47 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/26 00:29:31 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_applymaskthree(wchar_t a, t_save *save)
{
	char	c1;
	char	c2;
	char	c3;
	char	c4;

	c1 = ((a >> 18) & 0xF) | 0xF0;
	c2 = ((a >> 12) & 0x3F) | 0x80;
	c3 = ((a >> 6) & 0x3F) | 0x80;
	c4 = (a & 0x3F) | 0x80;
	ft_putchar_return(c1, save);
	ft_putchar_return(c2, save);
	ft_putchar_return(c3, save);
	ft_putchar_return(c4, save);
}

void	ft_applymasktwo(wchar_t a, t_save *save)
{
	char	c1;
	char	c2;
	char	c3;

	c1 = ((a >> 12) & 0x0F) | 0xE0;
	c2 = ((a >> 6) & 0x3F) | 0x80;
	c3 = (a & 0x3F) | 0x80;
	ft_putchar_return(c1, save);
	ft_putchar_return(c2, save);
	ft_putchar_return(c3, save);
}

void	ft_applymaskone(wchar_t a, t_save *save)
{
	char	c1;
	char	c2;

	c1 = ((a >> 6) & 0x1F) | 0xC0;
	c2 = (a & 0x3F) | 0x80;
	ft_putchar_return(c1, save);
	ft_putchar_return(c2, save);
}

void	ft_printuniw(wchar_t a, t_save *save, int length)
{
	char	*test;

	test = ft_itoabase(a, 2);
	length = ft_strlen(test);
	ft_memdel((void **)&test);
	if (length < 8 && save->nbarg > 0)
	{
		ft_putchar(a);
		save->nbarg--;
	}
	if (length >= 8 && length <= 11)
	{
		ft_applymaskone(a, save);
		save->nbarg = save->nbarg - 2;
	}
	if (length >= 12 && length <= 16)
	{
		ft_applymasktwo(a, save);
		save->nbarg = save->nbarg - 3;
	}
	if (length >= 17 && length <= 21)
	{
		ft_applymaskthree(a, save);
		save->nbarg = save->nbarg - 4;
	}
}

void	ft_printuni(t_save *save, wchar_t a)
{
	char	*test;
	int		length;

	test = ft_itoabase(a, 2);
	length = ft_strlen(test);
	ft_memdel((void **)&test);
	if (length < 8)
	{
		if (save->neg == 0)
			ft_checkoptionuni(save, 1);
		ft_putchar_return(a, save);
		if (save->neg == 1)
			ft_checkoptionuni(save, 1);
	}
	if (length >= 8 && length <= 11)
	{
		if (save->neg == 0)
			ft_checkoptionuni(save, 2);
		ft_applymaskone(a, save);
		if (save->neg == 1)
			ft_checkoptionuni(save, 2);
	}
	ft_printuni_two(save, a, length);
}
