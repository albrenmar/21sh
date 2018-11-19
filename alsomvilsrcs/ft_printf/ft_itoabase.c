/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 02:14:26 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 20:25:02 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fillstr(char *str, unsigned long long nb, int neg, int base)
{
	int	i;

	i = 0;
	while (nb >= (unsigned long long)base)
	{
		str[i++] = (nb % base < 10) ? (nb % base) + '0' : (nb % base) + 55;
		nb = nb / base;
	}
	str[i++] = (nb % base < 10) ? (nb % base) + '0' : (nb % base) + 55;
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
}

static int	ft_lenum(unsigned long long nb, int base)
{
	int	i;

	i = 0;
	while (nb >= (unsigned long long)base)
	{
		nb = nb / base;
		i++;
	}
	return (i + 1);
}

char		*ft_itoabase(unsigned long long nb, int base)
{
	int		len;
	int		neg;
	char	*str;

	neg = 0;
	len = ft_lenum(nb, base);
	if (!(str = ft_memalloc(sizeof(char) * (len + 1 + neg))))
		return (NULL);
	ft_fillstr(str, nb, neg, base);
	ft_strrev(str);
	return (str);
}
