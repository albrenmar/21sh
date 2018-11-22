/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 07:27:53 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 20:30:51 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (i > j)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		i--;
		j++;
	}
	return (str);
}
