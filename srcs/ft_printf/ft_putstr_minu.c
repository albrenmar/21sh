/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_minu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 12:41:16 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:38:42 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_putstr_minu(char *str, t_save *save, int test)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (test == 0)
		{
			if (str[i] >= 65 && str[i] <= 90)
				ft_putchar_return((str[i] + 32), save);
			else
				ft_putchar_return(str[i], save);
			i++;
		}
		else if (test == 1)
		{
			if (str[i] >= 97 && str[i] <= 122)
				ft_putchar_return((str[i] - 32), save);
			else
				ft_putchar_return(str[i], save);
			i++;
		}
	}
}
