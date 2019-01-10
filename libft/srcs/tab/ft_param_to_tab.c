/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:23:40 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:23:40 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

struct s_stock_par	*ft_param_to_tab(int ac, char **av)
{
	int				i;
	t_stock_par		*array;

	i = 0;
	array = (t_stock_par*)malloc(sizeof(t_stock_par) * (ac + 1));
	while (i < ac)
	{
		array[i].size_param = ft_strlen(av[i]);
		array[i].str = av[i];
		array[i].copy = ft_strdup(av[i]);
		array[i].tab = ft_split_whitespaces(av[i]);
		i++;
	}
	array[i].str = 0;
	return (array);
}
