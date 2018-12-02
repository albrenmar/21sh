/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/02 05:14:55 by bsiche           ###   ########.fr       */
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
	ft_putstr(g_tracking.prompt);
	ft_putstr(g_tracking.str);
}