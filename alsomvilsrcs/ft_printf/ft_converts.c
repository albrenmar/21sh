/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 03:36:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/26 00:35:43 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_converts_three(t_save *save, wchar_t *arg)
{
	int		i;

	i = 0;
	ft_checkoptioncharuni(arg, save);
	while (arg[i])
	{
		if (arg[i] && arg[i] >= 32 && arg[i] <= 126)
			i++;
		if (arg[i] > 126)
		{
			if ((arg[i] >= 0xD800 && arg[i] <= 0xDFFF)
					|| arg[i] > 0x10DFFF || arg[i] < 0)
			{
				save->start = NULL;
				save->retour = -1;
				return ;
			}
			i++;
		}
	}
	i = 0;
}

void	ft_converts_four(va_list test, t_save *save, wchar_t *arg)
{
	int		i;

	i = 0;
	arg = va_arg(test, wchar_t*);
	if (arg == NULL)
	{
		ft_putstr_return("(null)", save);
		return ;
	}
	if (save->precisionnull == 1)
	{
		if (save->largeur > 0)
			while (i++ < save->largeur)
				ft_putchar_return(' ', save);
		return ;
	}
	ft_converts_three(save, arg);
	while (arg[i] && i < save->spaceuni)
	{
		if (arg[i] && arg[i] >= 32 && arg[i] <= 126)
			ft_putchar_return(arg[i], save);
		if (arg[i] && arg[i] > 126)
			ft_printuniw(arg[i], save, 0);
		i++;
	}
}

void	ft_converts(va_list test, t_save *save)
{
	wchar_t	*arg;
	char	*argument;

	arg = NULL;
	if ((save->conversion == 'S' || (save->conversion == 's'
					&& save->flagl == 1)) && MB_CUR_MAX > 1)
		ft_converts_four(test, save, arg);
	else if ((save->conversion == 'S' || (save->conversion == 's'
					&& save->flagl == 1)) && MB_CUR_MAX <= 1)
		ft_converts_one(test, save);
	else
	{
		argument = va_arg(test, char*);
		if (argument == NULL)
		{
			argument = ft_strdup("(null)\0");
			ft_checkoptionchar(save, argument);
			ft_memdel((void **)&argument);
			return ;
		}
		ft_checkoptionchar(save, argument);
	}
}

void	ft_convertc_one(va_list test, t_save *save)
{
	char	argument;

	argument = (char)va_arg(test, int);
	if ((save->conversion == 'C' || (save->conversion == 'c'
					&& save->flagl == 1))
			&& argument == 0 && MB_CUR_MAX <= 1)
		save->retour = -1;
	if (save->conversion != 'c' && save->retour != -1)
		ft_putstr_return(save->start, save);
	ft_checkoptionchart(save, argument);
}

void	ft_convertc(va_list test, t_save *save)
{
	int		i;
	wchar_t	arg;

	i = 0;
	if ((save->conversion == 'C' || (save->conversion == 'c' && save->flagl))
			&& MB_CUR_MAX > 1)
	{
		arg = va_arg(test, wchar_t);
		if ((arg >= 0xD800 && arg <= 0xDFFF) || arg > 0x10DFFF || arg < 0)
		{
			save->start = NULL;
			save->retour = -1;
			return ;
		}
		else if (save->flagl == 0)
			ft_putstr_return(save->start, save);
		ft_printuni(save, arg);
	}
	else
		ft_convertc_one(test, save);
}
