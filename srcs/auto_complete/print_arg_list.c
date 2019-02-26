/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/24 03:17:37 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_check(void)
{
	int		flag;
	int		space;
	int		nb;

	flag = 0;
	if (g_tracking.aut->col_nbr == 0)
		return (1);
	space = g_tracking.aut->lin_nbr * g_tracking.aut->col_nbr;
	nb = lstcontainer_size(g_tracking.aut->comp_list);
	if (space < nb)
		return (1);
	else
		return (0);
}

char	*ft_joinline(int col_nbr, int i, t_ls *arg)
{
	char	*line;
	char	*sub;

	line = ft_strnew(0);
	sub = send_color(arg->color);
	if (sub != NULL)
		line = ft_strjoinfree(line, sub, 1);
	line = ft_strjoinfree(line, arg->name, 1);
	line = ft_strjoinfree(line, "\033[0m", 1);
	if ((i + 1) < col_nbr)
		line = ft_strjoinfree(line, arg->strpad, 1);
	return (line);
}

char	*ft_createline()
{
	int		i;
	t_list	*tmp;
	t_ls	*arg;
	int		col_nbr;
	char	*fake;

	tmp = g_tracking.aut->page_lst->firstelement;
	col_nbr = g_tracking.aut->col_nbr;
	fake = ft_strnew(0);
	while (tmp)
	{
		i = 0;
		while (i < col_nbr && tmp)
		{
			arg = tmp->content;
			if (ft_strcmp(arg->name, g_tracking.aut->to_add) == 0)
				fake = ft_strjoinfree(fake, "\033[7m", 1);
			fake = ft_strjoinfree(fake, ft_joinline(col_nbr, i, arg), 3);
			i++;
			tmp = tmp->next;
		}
		fake = ft_strjoinfree(fake, "\n", 1);
	}
	return (fake);
}

int		ft_menuline()
{
	char		*res;

//	if (ft_check() == 0)
//	{
		if (g_tracking.aut->menuline)
		{
			free(g_tracking.aut->menuline);
			g_tracking.aut->menuline = NULL;
		}
		g_tracking.aut->menuline = ft_createline();
		return (0);
//	}
//	else
//		g_tracking.aut->menuline = (ft_strdup("(╯°□°）╯︵ ┻━┻ Term size too small to display all possibilities"));
//	return (1);
}

void	back_up_add(void)
{
	int		y;
	int		ab;
	int		winx;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	ab += utf_strlen(g_tracking.aut->to_add);
	y = ab / g_tracking.terminfo->sizex;
	y = y - (g_tracking.pos->y);
	while (y != 0)
	{
		y--;
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
	}
}

int		print_menu(void)
{
	int		i;
	int		j;
	int		tmp;

	i = g_tracking.aut->line_up + 1;
	ft_putstr_nocar(g_tracking.aut->to_add);
	back_up_add();
	j = ft_menuline();
	tputs(tgetstr("do ", NULL), 1, yan_putchar);
	if (j == 0)
	{
		ft_putstr_nocar(g_tracking.aut->menuline);
		if (g_tracking.aut->page_nbr > 0)
			join_page_nbr();
		while (i > 0)
		{
			tputs(tgetstr("up ", NULL), 1, yan_putchar);
			i--;
		}
	}
	return (j);
}