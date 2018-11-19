/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converts_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:30:17 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/26 00:34:45 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checkoptioncharuni_one(wchar_t *arg, t_save *save)
{
	int		i;
	int		nbarg;
	int		length;
	char	*test;

	nbarg = 0;
	i = 0;
	while (arg[i] && i < save->spaceuni)
	{
		test = ft_itoabase(arg[i], 2);
		length = ft_strlen(test);
		ft_memdel((void **)&test);
		if (length < 8)
			nbarg++;
		else if (length >= 8 && length <= 11)
			nbarg = nbarg + 2;
		else if (length >= 12 && length <= 16)
			nbarg = nbarg + 3;
		else if (length >= 17 && length <= 21)
			nbarg = nbarg + 4;
		i++;
	}
	i = 0;
	while (i++ < (save->largeur - nbarg))
		ft_putchar_return(' ', save);
}

void	ft_checkoptioncharuni(wchar_t *arg, t_save *save)
{
	int		i;
	int		nbarg;
	int		length;
	char	*test;

	i = 0;
	nbarg = 0;
	while (arg[i++])
	{
		test = ft_itoabase(arg[i], 2);
		length = ft_strlen(test);
		ft_memdel((void **)&test);
		if (length < 8)
			nbarg++;
		else if (length >= 8 && length <= 11)
			nbarg = nbarg + 2;
		else if (length >= 12 && length <= 16)
			nbarg = nbarg + 3;
		else if (length >= 17 && length <= 21)
			nbarg = nbarg + 4;
		if ((save->precision > 0 && nbarg <= save->precision)
				|| save->precision == 0)
			save->spaceuni++;
	}
	ft_checkoptioncharuni_one(arg, save);
}

void	ft_converts_two(t_save *save, wchar_t *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] && arg[i] >= 32 && arg[i] <= 126)
			i++;
		if (arg[i] > 126)
		{
			if ((save->precision > 0 && i < save->precision)
					|| save->precision == 0)
			{
				if ((arg[i] >= 0xD800 && arg[i] <= 0xDFFF)
						|| arg[i] > 0x10DFFF || arg[i] < 0 || arg[i] > 255)
				{
					ft_memdel((void **)&save->start);
					save->start = NULL;
					save->retour = -1;
					return ;
				}
			}
			i++;
		}
	}
}

void	ft_converts_one(va_list test, t_save *save)
{
	int		i;
	wchar_t	*arg;

	i = 0;
	arg = va_arg(test, wchar_t*);
	if (save->precisionnull == 1)
	{
		if (save->largeur > 0)
		{
			while (i++ < save->largeur)
				ft_putchar_return(' ', save);
		}
		return ;
	}
	ft_converts_two(save, arg);
	ft_checkoptioncharuni(arg, save);
	i = 0;
	while (arg[i++] && save->nbarg > 0)
	{
		ft_putchar_return(arg[i], save);
		save->nbarg--;
	}
	while ((save->neg == 1 && i++ < save->spaceuni)
			|| (save->retour != -1 && save->retour < save->largeur))
		ft_putchar_return(' ', save);
}
