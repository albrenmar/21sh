/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 13:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/13 23:39:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		err_check(int a, int i, int j)
{
	char	*newstr;

	newstr = NULL;
	if (i + j > g_tracking.buffsize)
	{
		g_tracking.buffsize *= 2;
		newstr = malloc(sizeof(char) * g_tracking.buffsize);
		newstr = ft_strcpy(newstr, g_tracking.str);
		free(g_tracking.str);
		g_tracking.str = newstr;
	}
}

void		add_to_str(char *str)
{
	int		i;
	int		a;
	int		len_src;
	int		len_dest;

	if (str != NULL)
	{
		i = utf_strlen(str);
		a = g_tracking.pos->abs;
		if (!g_tracking.str)
			g_tracking.str = ft_strcpy(g_tracking.str, str);
		else
		{
			len_src = ft_strlen(str);
			len_dest = ft_strlen(g_tracking.str);
			a = utf_goto(g_tracking.str, a);
			err_check(a, len_dest, len_src);
			if (a > utf_strlen(g_tracking.str))
				a = ft_strlen(g_tracking.str);
			ft_memmove(g_tracking.str+a+len_src, g_tracking.str+a , len_dest- a+1);
  			ft_memcpy(g_tracking.str+a,str,len_src);
		}
		free(str);
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
		end = ft_strjoinfree(start, end, 3);
		free(g_tracking.str);
		g_tracking.str = malloc(sizeof(char) * g_tracking.buffsize);
		g_tracking.str = ft_strcpy(g_tracking.str, end);
		free(end);
		print_line();
		g_tracking.pos->abs -= 1;
		back_to_pos();
	}
}

void		rem_str(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i > 0)
	{
		rem_from_str();
		i--;
	}
}
