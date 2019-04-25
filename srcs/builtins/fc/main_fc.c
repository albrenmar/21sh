/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/24 13:45:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		editor_mode(t_fcparse *opt)
{
	ft_putendl("edit mode");
	opt->i = 0;
	if (opt->low && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = opt->low;
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
	create_fc_file(opt);
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
	if (opt->low && opt->max == -42)
	{
		opt->low = -15;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = -1;
	print_fc(opt);
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if ((opt->e == 1 && opt->s == 1) || (opt->e == 1 && opt->l == 1))
		return (fc_error(3, NULL));
	if ((opt->l == 1 && opt->s == 1) || (opt->l == 1 && opt->e == 1))
		return (fc_error(3, NULL));
	if ((opt->s == 1 && opt->n == 1) || (opt->e == 1 && opt->n == 1))
		return (fc_error(3, NULL));
	if (opt->e == 1)
		return (editor_mode(opt));
	if (opt->s == 1)
		return (no_edit_mode(opt));
	if (opt->l == 1)
		return (list_mode(opt));
	return (editor_mode(opt));
}

void	hist_set_unset(int i, t_fcparse *opt)
{
	t_list	*tmp;

	if (!g_tracking.mysh || !g_tracking.mysh->hist || !opt)
		return ;
	if (i == 0)
	{
		tmp = ft_lstgetlast(g_tracking.mysh->hist->lastelement);
		g_tracking.mysh->hist->lastelement = tmp->prev;
		opt->save_hist = ft_strdup(tmp->content);
		ft_lstdelone(tmp, 1);
		tmp = NULL;
	}
	if (i == 1)
	{
		if (!opt || opt->e == 1 || opt->s == 1)
			return ;
		else
		{
			if (write(0, "c", 0) != -1)
				lstcontainer_add(g_tracking.mysh->hist, ft_strdup(opt->save_hist));
		}
	}
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
	hist_set_unset(0, opt);
	while (av[count])
		count++;
	if (opt->i > count || (opt = fc_offset(av, opt)) == NULL)
		return (1);
	if (opt->err != 0)
		fc_error(2, NULL);
	char_to_index(opt);
	fc_mode(opt);
	hist_set_unset(1, opt);
	return (0);
}
