/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 02:51:24 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 02:57:07 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_bad_expansion(char *to_eval)
{
	char	*tmp;

	if (g_tracking.mysh->err_expend)
	{
		tmp = ft_strdup(to_eval);
		expand_transformer(&tmp, 0);
		if (!g_tracking.mysh->err_expend)
			return (1);
		ft_strdel(&tmp);
	}
	return (0);
}

int		check_expand_tab(char **tab_to_eval)
{
	char	**run_tab;
	int		i;

	run_tab = tab_to_eval;
	i = 0;
	while (run_tab[i])
		if (is_bad_expansion(run_tab[i++]))
			return (1);
	return (0);
}
