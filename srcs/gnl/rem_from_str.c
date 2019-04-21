/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_from_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 04:08:00 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/20 00:52:49 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		tmp_char_hist(void)
{
	if (g_tracking.tmp_hist)
		ft_strdel(&g_tracking.tmp_hist);
	g_tracking.tmp_hist = ft_strdup(g_tracking.str);
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
		end = ft_strjoinfree(start, end, 3);
		ft_free(g_tracking.str);
		g_tracking.str = ft_malloc(sizeof(char) * g_tracking.buffsize);
		g_tracking.str = ft_strcpy(g_tracking.str, end);
		ft_free(end);
		print_line();
		g_tracking.pos->abs -= 1;
		back_to_pos();
		tmp_char_hist();
	}
}

void		rem_from_str_del(void)
{
	int		a;
	int		b;
	char	*start;
	char	*end;

	b = g_tracking.pos->abs + 1;
	a = b - 1;
	if (g_tracking.str != NULL && b > 0)
	{
		a = utf_goto(g_tracking.str, a);
		b = utf_goto(g_tracking.str, b);
		start = ft_strsub(g_tracking.str, 0, a, 0);
		end = ft_strsub(g_tracking.str, b, ft_strlen(g_tracking.str), 0);
		end = ft_strjoinfree(start, end, 3);
		ft_free(g_tracking.str);
		g_tracking.str = ft_malloc(sizeof(char) * g_tracking.buffsize);
		g_tracking.str = ft_strcpy(g_tracking.str, end);
		ft_free(end);
		print_line();
		back_to_pos();
		tmp_char_hist();
	}
}

void		rem_str(char *str)
{
	int		i;

	i = ft_strlen(str);
	if (i > 0)
	{
		while (i > 0)
		{
			rem_from_str();
			i--;
		}
	}
}
