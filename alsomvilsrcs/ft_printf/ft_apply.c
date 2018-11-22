/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 23:38:09 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:23:44 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_apply_one(va_list test, t_save *save)
{
	if (save->conversion == 'o' || save->conversion == 'O')
	{
		ft_putstr_return(save->start, save);
		ft_convertpxou(test, save);
	}
	else if (save->conversion == 'x' || save->conversion == 'X')
	{
		ft_putstr_return(save->start, save);
		ft_convertx(test, save);
	}
	else if (save->conversion == 'C' || save->conversion == 'c')
	{
		if (save->conversion == 'c')
			ft_putstr_return(save->start, save);
		ft_convertc(test, save);
	}
	else if (save->conversion == '%')
	{
		ft_putstr_return(save->start, save);
		ft_convertpourcent(save);
	}
	return ;
}

void	ft_apply(va_list test, t_save *save)
{
	if (save->conversion == 'i' || save->conversion == 'd'
		|| save->conversion == 'D' || save->conversion == 'u'
		|| save->conversion == 'U')
	{
		ft_putstr_return(save->start, save);
		ft_convertdi(test, save);
	}
	else if (save->conversion == 's' || save->conversion == 'S')
	{
		ft_putstr_return(save->start, save);
		ft_converts(test, save);
	}
	else if (save->conversion == 'p')
	{
		ft_putstr_return(save->start, save);
		ft_convertp(test, save);
	}
	ft_apply_one(test, save);
}
