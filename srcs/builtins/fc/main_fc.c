/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 00:59:03 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
		lstcontainer_remove(g_tracking.mysh->hist, tmp, 1);
		tmp = NULL;
	}
	if (i == 1)
	{
		if (!opt || opt->e == 1 || opt->s == 1)
			return ;
		else
		{
			if (write(0, "c", 0) != -1)
			{
				if (ft_strcmp(opt->save_hist, "\n") != 0 && ft_strlen(opt->save_hist) > 0 && opt->save_hist[0] > 32)
					lstcontainer_add(g_tracking.mysh->hist, ft_strdup(opt->save_hist));
			}
		}
	}
}

void	free_opt(t_fcparse *opt)
{
	if (!opt)
		return ;
	ft_strdel(&opt->editor);
	ft_strdel(&opt->first);
	ft_strdel(&opt->last);
	ft_strdel(&opt->save_hist);
	ft_strdel(&opt->str);
	ft_free(opt);
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
	free_opt(opt);
	return (0);
}
