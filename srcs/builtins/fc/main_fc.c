/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/23 14:13:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		editor_mode(t_fcparse *opt)
{
	ft_putendl("edit mode");
	opt->i = 0;
	if (opt->max == -42)
		opt->max = opt->low;
	if (opt->low && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	if (opt->low == -42)
		opt->low = opt->max;
	ft_putstr("first nbr :");
	ft_putnbr(opt->low);
	ft_putchar('\n');
	ft_putstr("last nbr :");
	ft_putnbr(opt->max);
	ft_putchar('\n');
	ft_putstr("rev flag :");
	ft_putnbr(opt->r);
	ft_putchar('\n');
	return (0);
}

int		no_edit_mode(t_fcparse *opt)
{
	ft_putendl("no edit mode");
	opt->i = 0;
	return (0);
}

int		list_mode(t_fcparse *opt)
{
	ft_putendl("list mode");
	if (opt->max == -42)
		opt->max = -1;
	if (opt->low && opt->max == -42)
	{
		opt->low = -16;
		opt->max = -1;
	}
	ft_putstr("first nbr :");
	ft_putnbr(opt->low);
	ft_putchar('\n');
	ft_putstr("last nbr :");
	ft_putnbr(opt->max);
	ft_putchar('\n');
	ft_putstr("rev flag :");
	ft_putnbr(opt->r);
	ft_putchar('\n');
	opt->i = 0;
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if (opt->first)
	if ((opt->e == 1 && opt->s == 1) || (opt->e == 1 && opt->l == 1))
		return (fc_error(3));
	if ((opt->l == 1 && opt->s == 1) || (opt->l == 1 && opt->e == 1))
		return (fc_error(3));
	if ((opt->s == 1 && opt->n == 1) || (opt->e == 1 && opt->n == 1))
		return (fc_error(3));
	if (opt->e == 1)
		return (editor_mode(opt));
	if (opt->s == 1)
		return (no_edit_mode(opt));
	if (opt->l == 1)
		return (list_mode(opt));
	return (editor_mode(opt));
}

int		fc_builtin(void)
{
	char		**av;
	int			i;
	int			count;
	t_fcparse	*opt;

	av = g_tracking.g_tab_exec;
	opt = (fc_option(av));
	i = 0;
	count = 0;
	while (av[count])
		count++;
	if (opt->i > count || (opt = fc_offset(av, opt)) == NULL)
		return (1);
	if (opt->str)
		ft_putendl(opt->str);
	if (opt->err != 0)
		fc_error(2);
	ft_putstr("First : ");
	ft_putendl(opt->first);
	ft_putstr("last : ");
	ft_putendl(opt->last);
	char_to_index(opt);
	fc_mode(opt);
	return (0);
}
