/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuni_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:21:03 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/26 00:26:20 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printuni_two(t_save *save, wchar_t a, int length)
{
	if (length >= 12 && length <= 16)
	{
		if (save->neg == 0)
			ft_checkoptionuni(save, 3);
		ft_applymasktwo(a, save);
		if (save->neg == 1)
			ft_checkoptionuni(save, 3);
	}
	if (length >= 17 && length <= 21)
	{
		if (save->neg == 0)
			ft_checkoptionuni(save, 4);
		ft_applymaskthree(a, save);
		if (save->neg == 1)
			ft_checkoptionuni(save, 4);
	}
}
