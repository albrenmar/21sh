/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/09 23:28:22 by bsiche           ###   ########.fr       */
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
	line = ft_strjoinfree(line, send_color(arg->color), 1);
	line = ft_strjoinfree(line, arg->name, 1);
	line = ft_strjoinfree(line, "\033[0m", 1);
	if ((i + 1) < col_nbr)
		line = ft_strjoinfree(line, arg->strpad, 1);
	return (line);
}

char	*ft_createline(void)
{
	int		i;
	t_list	*tmp;
	t_ls	*arg;
	int		col_nbr;
	char	*fake;

	tmp = g_tracking.aut->comp_list->firstelement;
	col_nbr = g_tracking.aut->col_nbr;
	fake = ft_strnew(0);
	g_tracking.aut->line_up = 1;
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
		g_tracking.aut->line_up++;
	}
	return (fake);
}

void	ft_menuline(void)
{
	char		*res;

	if (ft_check() == 0)
		g_tracking.aut->menuline = ft_createline();
	else
		g_tracking.aut->menuline = (ft_strdup("(╯°□°）╯︵ ┻━┻ Term size too small to display all possibilities"));
}

void	print_menu(void)
{
	int		i;

	i = g_tracking.aut->line_up;
	ft_putstr(g_tracking.aut->to_add);
	ft_menuline();
	tputs(tgetstr("do ", NULL), 1, yan_putchar);
	ft_putstr(g_tracking.aut->menuline);
	while (i > 0)
	{
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
		i--;
	}
}