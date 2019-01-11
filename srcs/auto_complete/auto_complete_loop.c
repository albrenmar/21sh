/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/12 00:24:50 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	clean_up_autoc(void)
{
	free(g_tracking.aut->word);
	g_tracking.aut->word = NULL;
	free(g_tracking.aut->path);
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->comp_list)
	{
		ft_lstdel(g_tracking.aut->comp_list->firstelement, 1);
		g_tracking.aut->comp_list->firstelement = NULL;
	}
	free(g_tracking.aut->comp_list);
	g_tracking.aut->comp_list = NULL;
	free(g_tracking.aut);
	g_tracking.aut = NULL;
}

void	end_autocomplete(int i)
{
	print_line();
	back_to_pos();
	if (g_tracking.aut)
	{
		if (i == 1)
		{
			if(g_tracking.aut->type == 1)
				g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, "/", 1);
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

void	get_new(t_list *buf)
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
		if (tmp->strpermission[0] == 'd')
			g_tracking.aut->type = 1;
		else
			g_tracking.aut->type = 0;
		print_menu();
	}
}

void	completion_loop(t_list *buf)
{
	char			*new;
	int				i;

	tputs(tgetstr("vi", NULL), 1, yan_putchar);
	get_new(buf);
	i = g_tracking.aut->line_up;
	while (i > 0)
	{
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
		i--;
	}
	while ((i = read_loop()) != 0 && buf != NULL)
	{
		if (i == -1)
		{
			if (buf->prev == NULL)
				buf = ft_lstgetlast(buf);
			else
				buf = buf->prev;
			print_menu();
			get_new(buf);
		}
		if (i == 1)
		{
			if (buf->next == NULL)
				buf = ft_lstgetfirst(buf);
			else
				buf = buf->next;
			get_new(buf);
		}
	}
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
}
