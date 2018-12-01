/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/01 05:54:23 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_line(void)
{
	int		a;
	int		i;
	char	*end;
	char	*str;

	clear_screen3();
	ft_putstr(">");
	ft_putstr(g_tracking.str);
	/*
	i = g_tracking.pos->y * g_tracking.terminfo->sizex - g_tracking.pos->prompt;
	if (g_tracking.pos->y == 0)
	{
		ft_putstr(">");
		i += g_tracking.pos->prompt;
	}
	str = g_tracking.str;
	end = ft_strsub(str, i, ft_strlen(str), 0);
	ft_putstr(end);*/
}