/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/21 17:49:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_line(void)
{
	int		a;
	int		i;
	char	*end;
	char	*str;

	if (g_tracking.str != NULL)
	{
		clear_screen3();
		ft_putendl_fd(g_tracking.prompt, 2);
		ft_putstr_nocar(g_tracking.str);
	}
}

void	print_line_cpy(int start, int end)
{
	int		i;

	start = g_tracking.cpaste->b1;
	end = g_tracking.cpaste->b2;
	i = 0;
	if (end < start)
	{
		start = g_tracking.cpaste->b2;
		end = g_tracking.cpaste->b1;
	}
	start = utf_goto(g_tracking.str, start);
	end = utf_goto(g_tracking.str, end);
	clear_screen3();
	ft_putendl_fd(g_tracking.prompt, 2);
	while (g_tracking.str[i])
	{
		if (i == start)
			ft_putstr("\033[7m");
		if (i == end)
			ft_putstr("\033[0m");
		ft_putchar(g_tracking.str[i]);
		i++;
	}
	ft_putstr("\033[0m");
	back_to_pos();
}
