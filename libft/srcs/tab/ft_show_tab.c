/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:23:46 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:23:46 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_show_tab(struct s_stock_par *par)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (par[j].str != 0)
	{
		i = 0;
		ft_putstr(par[j].copy);
		ft_putchar('\n');
		ft_putnbr(par[j].size_param);
		ft_putchar('\n');
		while (par[j].tab[i])
		{
			ft_putstr(par[j].tab[i]);
			ft_putchar('\n');
			i++;
		}
		j++;
	}
}
