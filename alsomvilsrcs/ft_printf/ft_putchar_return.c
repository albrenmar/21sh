/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:56:50 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 22:08:48 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_return(char c, t_save *save)
{
	if (save->retour != -1)
	{
		write(setfd(1, 0), &c, 1);
		save->retour = save->retour + 1;
	}
}
