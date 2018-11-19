/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkoption.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:31:44 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 05:06:57 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checkoptionuni(t_save *save, int nb)
{
	while (nb < save->largeur)
	{
		ft_putchar_return(' ', save);
		nb++;
	}
}

void	ft_checkoptionchart(t_save *save, char argument)
{
	int		i;

	if (save->neg == 1)
		ft_putchar_return(argument, save);
	i = 1;
	while (i < save->largeur)
	{
		ft_putchar_return(' ', save);
		i++;
	}
	if (save->neg == 0)
		ft_putchar_return(argument, save);
}

void	ft_checkoptionchar_two(t_save *save, char *str)
{
	if (save->precision > 0)
	{
		while (str[save->i] && save->i < save->precision)
			ft_putchar_return(str[save->i++], save);
	}
	else if (save->precision == 0 && save->precisionnull == 1)
		return ;
	else
		ft_putstr_return(str, save);
}

void	ft_checkoptionchar_one(t_save *save, char *str, int *size)
{
	if (save->precision == 0 || save->precision > *size)
	{
		while (save->i++ < (save->largeur - *size))
			ft_putchar_return(' ', save);
		save->i = 0;
		while (str[save->i] && save->i < (*size))
		{
			if (save->precisionnull == 0)
				ft_putchar_return(str[save->i], save);
			else
				ft_putchar_return(' ', save);
			save->i++;
		}
	}
	else
	{
		while (save->i++ < (save->largeur - save->precision))
			ft_putchar_return(' ', save);
		save->i = 0;
		while (save->i < (save->precision))
		{
			ft_putchar_return(str[save->i], save);
			save->i++;
		}
	}
}

void	ft_checkoptionchar(t_save *save, char *str)
{
	int		size;

	size = ft_strlen(str);
	if (save->largeur > 0)
	{
		if (save->precision == 0 && save->neg == 1)
		{
			while (str[save->i] && save->i < (save->largeur - size))
				ft_putchar_return(str[save->i++], save);
			while (save->i++ < save->largeur)
				ft_putchar_return(' ', save);
		}
		else if (save->neg == 1)
		{
			while (str[save->i] && save->i < (save->precision))
				ft_putchar_return(str[save->i++], save);
			while (save->i++ < save->largeur)
				ft_putchar_return(' ', save);
		}
		else
			ft_checkoptionchar_one(save, str, &size);
		return ;
	}
	ft_checkoptionchar_two(save, str);
}
