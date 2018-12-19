/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 20:14:05 by bsiche            #+#    #+#             */
/*   Updated: 2018/07/18 19:01:28 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_easyprint(t_list *liste, char *option)
{
	t_list	*buf;
	t_ls	*tmp;
	int		g;

	g = checkoption(option, 'G');
	buf = ft_lstgetfirst(liste);
	if (g == 1)
		color(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		if (g == 1)
			ft_putcolor(tmp->color);
		ft_putendl(tmp->name);
		ft_putcolor(12);
		buf = buf->next;
	}
	return (0);
}

void	ft_step(t_list *liste, int nb, size_t nopad, int g)
{
	t_list	*buf;
	t_ls	*tmp;
	int		i;

	buf = liste;
	while (buf != NULL)
	{
		i = 0;
		tmp = buf->content;
		if (g == 1)
			ft_putcolor(tmp->color);
		if ((buf->index) > nopad)
		{
			free(tmp->name);
			tmp->name = ft_strtrim(tmp->name);
		}
		ft_putstr(tmp->name);
		while (i < nb - 1 && buf->next != NULL)
		{
			buf = buf->next;
			i++;
		}
		buf = buf->next;
	}
}

void	protoprint(t_list *liste, int nbrline, size_t nopad, int g)
{
	t_list	*buf;
	t_ls	*tmp;
	int		i;

	buf = ft_lstgetfirst(liste);
	tmp = buf->content;
	i = 0;
	while (i < nbrline && buf != NULL)
	{
		ft_step(buf, nbrline, nopad, g);
		ft_putchar('\n');
		buf = buf->next;
		i++;
	}
	liste = ft_lstgetfirst(liste);
}

int		get_coltab(t_list *liste, int g)
{
	size_t		nbrline;
	size_t		nbrelem;
	size_t		nopad;
	t_list		*buf;

	if (g == 1)
		color(liste);
	reindex(liste);
	buf = ft_lstgetfirst(liste);
	nbrelem = ft_lstgetlast(buf)->index + 1;
	nbrline = (nbrelem / ft_strpad(liste, g)) + 1;
	nopad = nbrelem - nbrline;
	protoprint(liste, nbrline, nopad, g);
	return (0);
}

int		ft_print(t_list *liste, char *option, int flag)
{
	t_ls	*tmp;
	int		a;

	a = checkoption(option, 'l');
	if (a == 0 && needstat(option) != 1)
		ft_mergesort(liste, 0);
	tmp = liste->content;
	if (checkoption(option, 'r') == 1)
		reverselist(liste);
	if (checkoption(option, '1') == 1 ||
		(a == 0 && checkoption(option, 'd') == 1))
		return (ft_easyprint(liste, option));
	if (a == 0)
	{
		get_coltab(liste, checkoption(option, 'G'));
		return (0);
	}
	else
	{
		if (flag != 1 && tmp->issimple != 1)
			ft_total(liste);
		ft_printl(liste, checkoption(option, 'G'));
	}
	return (0);
}
