/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/21 15:40:19 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_return(void)
{
	ft_putchar('\n');
	ft_putstr(">");
	ft_putstr("Danger zone");
	free(g_tracking.str);
	g_tracking.pos->abs = 0;
	g_tracking.str = ft_strnew(0);
}

void	correct_pos(void) 
{
	int		x;
	int		y;
	int		ab;

	ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	g_tracking.pos->x = ab % g_tracking.terminfo->sizex;
	g_tracking.pos->y = ab / g_tracking.terminfo->sizex;
}

void	update_pos(void)
{
	int		x;
	int		y;
	char	*test;

	test = tgetstr("cm", NULL);
	correct_pos();
	x = g_tracking.pos->x;
	y = g_tracking.pos->y;
	tputs(tgoto(test, x, y), 1, yan_putchar);
}

int		ft_cursor(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		if (g_tracking.pos->abs > 0)
		{
			g_tracking.pos->abs -= 1;
			ft_putnbr(g_tracking.pos->abs);
			sleep(1);
		}
	if (K_RIGHT)
		if ((g_tracking.pos->abs) <= ft_strlen(g_tracking.str))
			g_tracking.pos->abs += 1;
	if (K_DOWN)
		ft_putendl("down");
	if (K_UP)
		ft_putendl("UP");
	return (1);
}

int		ft_exec_key(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		if (g_tracking.pos->abs > 0)
			g_tracking.pos->abs -= 1;
	if (ft_strcmp(str, K_RIGHT) == 0)
		if ((g_tracking.pos->abs) < utf_strlen(g_tracking.str))
			g_tracking.pos->abs += 1;
	if (ft_strcmp(str, K_UP) == 0)
		if ((g_tracking.pos->y) > 0)
			g_tracking.pos->y -= 1;
	if (ft_strcmp(str, K_DOWN) == 0)
		if ((g_tracking.pos->y) < 10)
			g_tracking.pos->y += 1;
	if (ft_strcmp(str, K_DEL) == 0)
		rem_from_str();
	return (1);
}

int		is_cmd(char *str)
{
	int		i;
	t_list	*tmp;
	int		flag;

	i = ft_strlen(str);
	tmp = g_tracking.key_list->firstelement;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->content, i) == 0)
			flag++;
		if (strlen(tmp->content) == i && ft_strncmp(str, tmp->content, i) == 0)
			return (ft_exec_key(str));
		tmp = tmp->next;
	}
	if (flag == 0)
		return (3);
	return (0);
}

int	single_key(char c)
{
	if (c == K_BKSP)
	{
		rem_from_str();
		return (1);
	}
	if (c == 10 || c == 13)
	{
		ft_return();
		return (1);
	}
	return (0);
}

void	readloop(void)
{
	char	c;
	char	*str;
	int		i;

	str = ft_strnew(2);
	i = 0;
	read(STDERR_FILENO, &c, 1);
	str = ft_strjoinchar(str, c, 1);
	i = single_key(c);
	if (c < 32)
	{
		while (i == 0)
		{
			read(STDERR_FILENO, &c, 1);
			str = ft_strjoinchar(str, c, 1);
			i = is_cmd(str);
			if (i == 3)
				break ;
		}
	}
	if (i == 1)
		free(str);
	else
		add_to_str(str);
}

int		get_key(void)
{
	char	*test;

	ft_putstr(">");
	while (1)
	{
		readloop();
		clear_screen2();
		ft_putstr(">");
		ft_putstr(g_tracking.str);
		update_pos();
	}
	return (0);
}
