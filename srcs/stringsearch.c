/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 13:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/02 05:14:52 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		add_to_str(char *str)
{
	int		i;
	int		a;
	char	*start;
	char	*end;

	if (str != NULL)
	{
		i = utf_strlen(str);
		a = g_tracking.pos->abs;
		if (!g_tracking.str)
			g_tracking.str = ft_strdup(str);
		else
		{
			a = utf_goto(g_tracking.str, a);
			start = ft_strsub(g_tracking.str, 0, a, 0);
			end = ft_strsub(g_tracking.str, a, ft_strlen(g_tracking.str), 0);
			start = ft_strjoin(start, str, 3);
			free(g_tracking.str);
			g_tracking.str = ft_strjoin(start, end, 3);
		}
		print_line();
		g_tracking.pos->abs += i;
		back_to_pos();
	}
}

void		rem_from_str(void)
{
	int		a;
	int		b;
	char	*start;
	char	*end;

	b = g_tracking.pos->abs;
	a = b - 1;
	if (g_tracking.str != NULL && b > 0)
	{
		a = utf_goto(g_tracking.str, a);
		b = utf_goto(g_tracking.str, b);
		start = ft_strsub(g_tracking.str, 0, a, 0);
		end = ft_strsub(g_tracking.str, b, ft_strlen(g_tracking.str), 0);
		g_tracking.str = ft_strjoin(start, end, 3);
		print_line();
		g_tracking.pos->abs -= 1;
		back_to_pos();
	}
}
