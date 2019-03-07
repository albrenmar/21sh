/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 03:46:59 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/03/01 07:09:53 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

<<<<<<< HEAD
=======
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
			if (g_tracking.aut->type == 2)
				g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, "} ", 1);
			if ((g_tracking.aut->type != 2) && (g_tracking.aut->type != 1))
				g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, " ", 1);
			add_to_str(g_tracking.aut->to_add);
			g_tracking.aut->to_add = NULL;
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

>>>>>>> alsomvil
int		read_loop(void)
{
	long c;

	c = 0;
	if (lstcontainer_size(g_tracking.aut->comp_list) == 1)
<<<<<<< HEAD
		return (end_autocomplete(1));
=======
	{
		end_autocomplete(1);
		return (0);
	}
>>>>>>> alsomvil
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
<<<<<<< HEAD
		return (end_autocomplete(1));
	else
		return (end_autocomplete(0));
=======
	{
		end_autocomplete(1);
		return (0);
	}
	else
	{
		end_autocomplete(0);
		return (0);
	}
>>>>>>> alsomvil
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
		{
			free(g_tracking.aut->to_add);
			g_tracking.aut->to_add = NULL;
		}
		g_tracking.aut->to_add = ft_strdup(tmp->name);
		if (g_tracking.aut->type != 2)
		{
			if (tmp->strpermission[0] == 'd' || tmp->strpermission[0] == 'l')
				g_tracking.aut->type = 1;
			else
				g_tracking.aut->type = 0;
		}
		return (print_menu());
	}
	return (0);
}

<<<<<<< HEAD
void	actual_loop(t_lstcontainer *list)
=======
void	completion_loop(t_lstcontainer *list)
>>>>>>> alsomvil
{
	char			*new;
	t_lstcontainer	*page;
	t_list			*buf;
	int				i;

<<<<<<< HEAD
=======
	tputs(tgetstr("vi", NULL), 1, yan_putchar);
	line_per_page();
>>>>>>> alsomvil
	g_tracking.aut->page_lst = build_page_lst(list);
	buf = g_tracking.aut->page_lst->firstelement;
	if (!buf)
		exit(0);
	get_new(buf);
	i = g_tracking.aut->line_up;
	while ((i = read_loop()) != 0 && buf != NULL)
	{
<<<<<<< HEAD
		if (i == 3 || i == -3)
=======
		if (i == 3 || i == - 3)
>>>>>>> alsomvil
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
<<<<<<< HEAD
}

void	back_up_err(char *err)
{
	int		y;
	int		ab;
	int		winx;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	ab += utf_strlen(err);
	y = ab / g_tracking.terminfo->sizex;
	y = y - (g_tracking.pos->y);
	while (y != 0)
	{
		y--;
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
	}
}

void	completion_loop(t_lstcontainer *list)
{
	char	*err;

	err = NULL;
	if (g_tracking.aut->err == 0)
	{
		tputs(tgetstr("vi", NULL), 1, yan_putchar);
		line_per_page();
		actual_loop(list);
		tputs(tgetstr("ve", NULL), 1, yan_putchar);
	}
	if (g_tracking.aut->err == 2)
	{
		err = ft_strdup("Term size too small");
		tputs(tgetstr("do ", NULL), 1, yan_putchar);
		ft_putendl_fd(err, 2);
		back_up_err(err);
	}
=======
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
>>>>>>> alsomvil
}
