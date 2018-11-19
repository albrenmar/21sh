/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removestruct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:56:21 by alsomvil          #+#    #+#             */
/*   Updated: 2018/04/24 04:28:34 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_removestruct(t_save *save, int i)
{
	save->precision = 0;
	save->precisionnull = 0;
	save->largeur = 0;
	save->nbarg = 0;
	save->spaceuni = 0;
	save->conversion = 0;
	save->space = 0;
	save->pos = 0;
	save->dieze = 0;
	save->zero = 0;
	save->neg = 0;
	save->flagh = 0;
	save->flaghh = 0;
	save->flagl = 0;
	save->flagll = 0;
	save->flagj = 0;
	save->flagz = 0;
	save->i = 0;
	if (i == 1)
	{
		save->retour = 0;
		save->start = NULL;
	}
	ft_memdel((void **)&save->start);
}
