/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/05 15:32:23 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	print_line(void)
{
	int		a;
	int		i;
	char	*end;
	char	*str;

	if (g_tracking.str != NULL)
	{
		clear_screen3();
		ft_dprintf(2, "%s", g_tracking.prompt);
		ft_putstr(g_tracking.str);
	}
}