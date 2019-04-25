/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:40:35 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/25 23:59:11 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	get_neg_offset(t_fcparse *opt)
{
	t_list		*tmp;
	int			i;

	tmp = ft_lstgetlast(g_tracking.mysh->hist->lastelement);
	i = 0;
	if (opt->low < 0)
	{
		i = opt->low + 1;
		while (i < 0)
		{
			tmp = tmp->prev;
			i++;
		}
		opt->low = tmp->index;
	}
	tmp = ft_lstgetlast(g_tracking.mysh->hist->lastelement);
	if (opt->max < 0)
	{
		i = opt->max + 1;
		while (i < 0)
		{
			tmp = tmp->prev;
			i++;
		}
		opt->max = tmp->index;
	}
}

void	rev_print(t_fcparse *opt)
{
	t_list		*tmp;

	tmp = ft_lstget(opt->max, g_tracking.mysh->hist->firstelement);
	while (tmp && (int)tmp->index >= (opt->low - 1))
	{
		if (opt->n != 1)
		{
			ft_putnbr(tmp->index + 1);
			ft_putstr(" :");
		}
		ft_putendl(tmp->content);
		tmp = tmp->prev;
	}
}

void	print_fc(t_fcparse *opt)
{
	t_list		*tmp;

	if (!opt)
		return ;
	get_neg_offset(opt);
	if (opt->r == 0)
	{
		tmp = ft_lstget(opt->low - 1, g_tracking.mysh->hist->firstelement);
		while (tmp && (int)tmp->index < (opt->max + 1))
		{
			if (opt->n != 1)
			{
				ft_putnbr(tmp->index + 1);
				ft_putstr(" :");
			}
			ft_putendl(tmp->content);
			tmp = tmp->next;
		}
	}
	else
		rev_print(opt);
}
