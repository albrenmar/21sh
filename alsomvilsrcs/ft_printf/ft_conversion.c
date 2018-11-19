/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 07:07:13 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:47:38 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checkflag(t_save *save, char *str, int *i)
{
	int		j;

	j = 0;
	if (str[j] == 'h')
	{
		if (str[j + 1] && str[j + 1] == 'h')
		{
			save->flaghh = 1;
			(*i)++;
			j++;
		}
		else
			save->flagh = 1;
	}
	if (str[j] == 'l')
	{
		if (str[j + 1] && str[j + 1] == 'l')
		{
			save->flagll = 1;
			(*i)++;
			j++;
		}
		else
			save->flagl = 1;
	}
}

void	ft_checkoptionone(t_save *save, char *str, int *i)
{
	if (str[0] == '#')
		save->dieze = 1;
	else if (str[0] == '0')
		save->zero = 1;
	else if (str[0] == '-')
		save->neg = 1;
	else if (str[0] == ' ')
		save->space = 1;
	else if (str[0] == '+')
		save->pos = 1;
	else if (str[0] == 'j')
		save->flagj = 1;
	else if (str[0] == 'z')
		save->flagz = 1;
	else
		ft_checkflag(save, str, i);
	(*i)++;
}

void	ft_checksize(t_save *save, char *str, int *i, int temp)
{
	int		n;
	int		j;
	char	*stock;
	int		test;

	n = 1;
	j = 0;
	test = 0;
	if (str[j] >= '1' && str[j] <= '9' && *i < temp)
	{
		test = j;
		j++;
		while (str[j] && str[j] >= '0' && str[j] <= '9' && *i < temp)
		{
			j++;
			(*i)++;
			n++;
		}
		stock = ft_strndup(&str[test], n);
		save->largeur = ft_atoi(stock);
		ft_memdel((void **)&stock);
	}
	if (*i < temp)
		ft_checkoptionone(save, str, i);
}

void	ft_stockmodif_one(t_save *save, char *str, int *i)
{
	int		test;
	int		n;
	char	*stock;

	n = 0;
	if (str[*i + 1] >= '1' && str[*i + 1] <= '9')
	{
		(*i)++;
		test = *i;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			(*i)++;
			n++;
		}
		stock = ft_strndup(&str[test], n);
		save->precision = ft_atoi(stock);
		ft_memdel((void **)&stock);
	}
	else
	{
		save->precision = 0;
		save->precisionnull = 1;
		(*i)++;
	}
}

int		ft_stockmodif(t_save *save, char *str, int i, int temp)
{
	int		test;
	int		n;

	test = 0;
	n = 0;
	while (str[i] && i < temp)
	{
		if (str[i] == '.')
			ft_stockmodif_one(save, str, &i);
		if (i < temp)
			ft_checksize(save, &str[i], &i, temp);
	}
	return (i + 1);
}
