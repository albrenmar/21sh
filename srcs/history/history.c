/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/26 15:09:37 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			history_builtin_minus_error(int i, char flags)
{
	if (g_tracking.g_tab_exec[1][i] != 'c'\
		&& g_tracking.g_tab_exec[1][i] != 'd'\
		&& g_tracking.g_tab_exec[1][i] != 'a'\
		&& g_tracking.g_tab_exec[1][i] != 'n'\
		&& g_tracking.g_tab_exec[1][i] != 'r'\
		&& g_tracking.g_tab_exec[1][i] != 'w'\
		&& g_tracking.g_tab_exec[1][i] != 'p'\
		&& g_tracking.g_tab_exec[1][i] != 's'\
		&& flags == 0)
	{
		ft_putendl_fd("history -[ardcwnps]", 2);
		return (0);
	}
	return (1);
}

char		history_builtin_minus_check(int i, char flags)
{
	if (!(flags & 64) && g_tracking.g_tab_exec[1][i] == 'p'\
	&& (flags |= 64))
		history_builtin_p();
	if (!(flags & 128) && g_tracking.g_tab_exec[1][i] == 's'\
	&& (flags |= 128) && ft_strchr(g_tracking.g_tab_exec[1], 'p') == NULL)
		history_builtin_s();
	return (flags);
}

void		history_builtin_minus(void)
{
	int		i;
	char	flags;

	i = 0;
	flags = 0;
	while (g_tracking.g_tab_exec[1][i++])
	{
		if (history_builtin_minus_error(i, flags) == 0)
			return ;
		if (!(flags & 1) && g_tracking.g_tab_exec[1][i] == 'c' && (flags |= 1))
			g_tracking.mysh->hist = hist_free();
		if (!(flags & 2) && g_tracking.g_tab_exec[1][i] == 'd' && (flags |= 2))
			history_builtin_delete_index(i);
		if (!(flags & 4) && g_tracking.g_tab_exec[1][i] == 'a' && (flags |= 4))
			hist_save_file(g_tracking.mysh->hist);
		if (!(flags & 8) && g_tracking.g_tab_exec[1][i] == 'r' && (flags |= 8))
			hist_file_to_lst();
		if (!(flags & 16) && g_tracking.g_tab_exec[1][i] == 'w'\
		&& (flags |= 16))
			hist_save_file_w(g_tracking.g_tab_exec[2]);
		if (!(flags & 32) && g_tracking.g_tab_exec[1][i] == 'n'\
		&& (flags |= 32))
			hist_file_to_lst();
		flags = history_builtin_minus_check(i, flags);
	}
}

void		history_builtin(void)
{
	if (g_tracking.g_tab_exec[1] == NULL)
		hist_print(g_tracking.mysh->hist);
	else
	{
		if (g_tracking.g_tab_exec[1][0] == '-')
			history_builtin_minus();
		else if (ft_isdigit_str(g_tracking.g_tab_exec[1]))
			history_builtin_digit();
		else
			ft_putendl_fd("history argument need to be digit", 2);
	}
}
