/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertpxou.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:40:31 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 05:05:13 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convertx_one(va_list test, t_save *save)
{
	intmax_t	check;
	char		*temp;

	if ((save->conversion == 'x' || save->conversion == 'X')
			&& (save->flagh || save->flaghh) && !save->flagj)
	{
		check = va_arg(test, int);
		if ((check <= 255 && save->flaghh) || !save->flaghh)
			temp = ft_itoabase(check, 16);
		else
			temp = ft_itoabase((char)check, 16);
		if (check == 0)
			save->dieze = 0;
		ft_applyoptionx(temp, save);
		ft_memdel((void **)&temp);
	}
	else if (save->flagl || save->flagll || save->flagj)
	{
		check = va_arg(test, long long);
		temp = ft_itoabase(check, 16);
		ft_applyoptionx(temp, save);
		ft_memdel((void **)&temp);
	}
}

void	ft_convertx(va_list test, t_save *save)
{
	intmax_t	check;
	char		*temp;

	check = 0;
	temp = NULL;
	if ((save->conversion == 'x' || save->conversion == 'X')
			&& !save->flagll && !save->flagl && !save->flagh
			&& !save->flaghh && !save->flagj)
	{
		if (save->flagz == 1)
			check = (intmax_t)va_arg(test, size_t);
		else
			check = va_arg(test, unsigned int);
		if (check == 0 && save->largeur == 0)
		{
			if (save->precisionnull == 0)
				ft_putchar_return('0', save);
			return ;
		}
		temp = ft_itoabase(check, 16);
		ft_applyoptionx(temp, save);
		ft_memdel((void **)&temp);
	}
	ft_convertx_one(test, save);
}

void	ft_converto_two(va_list test, t_save *save, intmax_t arg, char *est)
{
	arg = va_arg(test, int);
	if (save->conversion == 'o' && save->flaghh && !save->flagj
			&& !save->flagz && !save->flagl && !save->flagll)
		est = ft_itoabase((unsigned char)arg, 8);
	else if (save->conversion == 'o' && save->flagh && !save->flagj
			&& !save->flagz && !save->flagl && !save->flagll)
		est = ft_itoabase((unsigned short int)arg, 8);
	else if ((arg <= 255 && save->flaghh) || !save->flaghh)
		est = ft_itoabase(arg, 8);
	ft_applyoptiono(est, save, 0);
	ft_memdel((void **)&est);
}

void	ft_converto_one(va_list test, t_save *save)
{
	intmax_t		arg;
	char			*est;

	arg = 0;
	est = NULL;
	if ((save->conversion == 'o' && save->flagl && save->flagll)
			|| save->conversion == 'O')
	{
		arg = va_arg(test, unsigned long long);
		est = ft_itoabase(arg, 8);
		ft_applyoptiono(est, save, 0);
	}
	else if (save->conversion == 'o' && save->flagz)
	{
		arg = va_arg(test, size_t);
		est = ft_itoabase(arg, 8);
		ft_applyoptiono(est, save, 0);
	}
	else
	{
		ft_converto_two(test, save, arg, est);
	}
}

void	ft_convertpxou(va_list test, t_save *save)
{
	intmax_t		argl;
	char			*est;

	est = NULL;
	if (save->conversion == 'o' && !save->flagl && !save->flagll
			&& !save->flagh && !save->flaghh)
	{
		if (save->flagz == 1)
			argl = (intmax_t)va_arg(test, size_t);
		else
			argl = va_arg(test, int);
		if (save->conversion == 'o' && !save->flagj && !save->flagz)
			est = ft_itoabase((unsigned int)argl, 8);
		else
			est = ft_itoabase(argl, 8);
		ft_applyoptiono(est, save, 0);
	}
	else
		ft_converto_one(test, save);
	ft_memdel((void **)&est);
}
