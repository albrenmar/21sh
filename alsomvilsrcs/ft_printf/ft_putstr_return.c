/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:59:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 20:26:32 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_return(char const *s, t_save *save)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		ft_putchar_return(s[i], save);
		i++;
	}
}
