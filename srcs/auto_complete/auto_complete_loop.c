/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/20 06:52:36 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	end_autocomplete(int i)
{
	print_line();
	back_to_pos();
	if (g_tracking.aut)
	{
		if (i == 1)
		{
			if (g_tracking.aut->type == 1)
				escape_path();
			else
				g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, " ", 1);
			add_to_str(g_tracking.aut->to_add);
		}
		else
		{
			if (g_tracking.aut->word)
			{
				add_to_str(g_tracking.aut->word);
				g_tracking.aut->word = NULL;
			}
		}
	}
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
}

int		read_loop(void)
{
	long c;

	c = 0;
	if (lstcontainer_size(g_tracking.aut->comp_list) == 1)
	{
		end_autocomplete(1);
		return (0);
	}
	read(STDERR_FILENO, &c, 8);
	if (c == 4479771)
		return (-1);
	if (c == 4414235 || c == K_TAB)
		return (1);
	if (c == 4348699)
		return (2);
	if (c == 4283163)
		return (-2);
	if (c == 2117425947)
		return (-3);
	if (c == 2117491483)
		return (3);
	if (c == K_RTN || c == K_SPC)
	{
		end_autocomplete(1);
		return (0);
	}
	else
	{
		end_autocomplete(0);
		return (0);
	}
}

int		get_new(t_list *buf)
{
	t_ls		*tmp;
	char		*menu_line;

	if (buf)
	{
		print_line();
		back_to_pos();
		tmp = buf->content;
		if (g_tracking.aut->to_add)
			free(g_tracking.aut->to_add);
		g_tracking.aut->to_add = ft_strdup(tmp->name);
		if (tmp->strpermission[0] == 'd' || tmp->strpermission[0] == 'l')
			g_tracking.aut->type = 1;
		else
			g_tracking.aut->type = 0;
		return (print_menu());
	}
	return (0);
}

void	completion_loop(t_lstcontainer *list)
{
	char			*new;
	t_lstcontainer	*page;
	t_list			*buf;
	int				i;

	tputs(tgetstr("vi", NULL), 1, yan_putchar);
	line_per_page();
	g_tracking.aut->page_lst = build_page_lst(list);
	buf = g_tracking.aut->page_lst->firstelement;
	get_new(buf);
	i = g_tracking.aut->line_up;
	while ((i = read_loop()) != 0 && buf != NULL)
	{
		if (i == 3 || i == - 3)
		{
			if (g_tracking.aut->page_nbr > 0)
			{
				change_page(i, list);
				buf = g_tracking.aut->page_lst->firstelement;
			}
		}
		else
			buf = move_arround(buf, i);
		get_new(buf);
	}
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
}
