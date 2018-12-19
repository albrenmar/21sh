/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 03:04:27 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:21:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		colordir(t_ls *tmp)
{
	if (tmp->strpermission[8] == 'w')
	{
		if (tmp->strpermission[9] == 't' || tmp->strpermission[9] == 'T')
		{
			tmp->color = 1;
			return (0);
		}
		else
			tmp->color = 2;
		return (0);
	}
	tmp->color = 3;
	return (0);
}

int		colorexe(t_ls *tmp)
{
	if (tmp->strpermission[3] == 's' || tmp->strpermission[3] == 'S')
	{
		tmp->color = 4;
		return (0);
	}
	if (tmp->strpermission[6] == 's' || tmp->strpermission[6] == 'S')
	{
		tmp->color = 5;
		return (0);
	}
	tmp->color = 6;
	return (0);
}

int		colorspe(t_ls *tmp)
{
	if (tmp->strpermission[0] == 'b')
	{
		tmp->color = 9;
		return (0);
	}
	if (tmp->strpermission[0] == 'c')
	{
		tmp->color = 10;
		return (0);
	}
	if (tmp->strpermission[0] == 's')
	{
		tmp->color = 11;
		return (0);
	}
	return (0);
}

void	color(t_list *liste)
{
	t_list	*buf;
	t_ls	*tmp;
	char	type;

	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		type = tmp->strpermission[0];
		if (type == 'd')
			colordir(tmp);
		if (type == '-' && tmp->strpermission[3] == 'x')
			colorexe(tmp);
		if (type == 'p')
		{
			tmp->color = 7;
		}
		if (type == 'l')
		{
			tmp->color = 8;
		}
		else
			colorspe(tmp);
		buf = buf->next;
	}
}

void	ft_putcolor(int i)
{
	if (i == 1)
		ft_putstr("\033[30;42m");
	if (i == 2)
		ft_putstr("\033[43m");
	if (i == 3)
		ft_putstr("\033[36;1m");
	if (i == 4)
		ft_putstr("\033[30;41m");
	if (i == 5)
		ft_putstr("\033[30;46m");
	if (i == 6)
		ft_putstr("\033[31m");
	if (i == 7)
		ft_putstr("\033[33m");
	if (i == 8)
		ft_putstr("\033[35m");
	if (i == 9)
		ft_putstr("\033[34;46m");
	if (i == 10)
		ft_putstr("\033[34;43m");
	if (i == 11)
		ft_putstr("\033[32m");
	if (i == 12)
		ft_putstr("\033[0m");
}
