/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 11:02:46 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

// history builtin for delete index option
void		history_builtin_delete_index(int j)
{
	char tmp[100000];
	int i[2];
	i[0] = 0;
	i[1] = 0;
	if (!(g_tracking.g_tab_exec[1][j+1]) && (g_tracking.g_tab_exec[2]))
	{
		if (ft_isdigit(g_tracking.g_tab_exec[2][i[1]]))
		{
			while (g_tracking.g_tab_exec[2][i[1]])
			{
				if (ft_isdigit(g_tracking.g_tab_exec[2][i[1]]) && i[1] <= 100000)
				{
					tmp[i[0]] = g_tracking.g_tab_exec[2][i[1]];
					i[1]++;
					j++;
				}
				else
				{
					ft_putendl_fd("history position out of range", 2);
					return;
				}
			}
		}
		else
		{
			ft_putendl_fd("history position out of range", 2);
			return;
		}
	}
	else if (!(g_tracking.g_tab_exec[1][j+1]) && !(g_tracking.g_tab_exec[2]))
	{
		ft_putendl_fd("history -d require valid argument: history -d [digit]",2);
		return;
	}
	else if (ft_isdigit(g_tracking.g_tab_exec[1][j+1]))
	{
		j++;
		while (g_tracking.g_tab_exec[1][j])
		{
			if (ft_isdigit(g_tracking.g_tab_exec[1][j]) && j <= 100000)
			{
				tmp[i[0]] = g_tracking.g_tab_exec[1][j];
				i[0]++;
				j++;
			}
			else
			{
				ft_putendl_fd("history position out of range", 2);
				return;
			}
		}
	}
	if (g_tracking.mysh->hist)
		g_tracking.mysh->hist = hist_delete_index(g_tracking.mysh->hist, ft_atoi(tmp));
}

// Dispatch the action and do the history builtin
// void		history_builtin(void)
// {
// 	int i = 0;
// 	char flags = 0;

// 	if (g_tracking.g_tab_exec[1] == NULL)
// 		hist_print(g_tracking.mysh->hist);
// 	else
// 	{
// 		if (g_tracking.g_tab_exec[1][0] == '-')
// 		{
// 			while (g_tracking.g_tab_exec[1][i])
// 			{
// 				if (!(flags & 1) && g_tracking.g_tab_exec[1][i] == 'c' && (flags |= 1))
// 					free_hist();
// 				// BUG WHEN -CDXXXXX 
// 				if (!(flags & 2) && g_tracking.g_tab_exec[1][i] == 'd' && (flags |= 2))
// 					history_builtin_delete_index(i);
// 				if (!(flags & 4) && g_tracking.g_tab_exec[1][i] == 'a' && (flags |= 4))
// 					hist_save_file(g_tracking.mysh->hist);
// 				if (!(flags & 8) && g_tracking.g_tab_exec[1][i] == 'r' && (flags |= 8))
// 					hist_file_to_lst();
// 				if (!(flags & 16) && g_tracking.g_tab_exec[1][i] == 'w' && (flags |= 16))
// 					hist_save_file(g_tracking.mysh->hist);
// 				i++;
// 			}
// 			i = 1;
// 		}
// 	}
// }

void		history_builtin_minus(void)
{
	int i;
	char flags;

	i = 1;
	flags = 0;
	while (g_tracking.g_tab_exec[1][i])
			{
				if (g_tracking.g_tab_exec[1][i] != 'c' && g_tracking.g_tab_exec[1][i] != 'd' && g_tracking.g_tab_exec[1][i] != 'a' \
				&& g_tracking.g_tab_exec[1][i] != 'n' && g_tracking.g_tab_exec[1][i] != 'r' && g_tracking.g_tab_exec[1][i] != 'w' \
				&& g_tracking.g_tab_exec[1][i] != 'p' && g_tracking.g_tab_exec[1][i] != 's')
				{
					ft_putendl_fd("history -[ardcwnps]", 2);
					return;
				}
				if (!(flags & 1) && g_tracking.g_tab_exec[1][i] == 'c' && (flags |= 1))
					g_tracking.mysh->hist = hist_free();
				if (!(flags & 2) && g_tracking.g_tab_exec[1][i] == 'd' && (flags |= 2))
					history_builtin_delete_index(i);
				if (!(flags & 4) && g_tracking.g_tab_exec[1][i] == 'a' && (flags |= 4))
					hist_save_file(g_tracking.mysh->hist);
				if (!(flags & 8) && g_tracking.g_tab_exec[1][i] == 'r' && (flags |= 8))
					hist_file_to_lst();
				if (!(flags & 16) && g_tracking.g_tab_exec[1][i] == 'w' && (flags |= 16))
					hist_save_file_w(g_tracking.g_tab_exec[2]);
				if (!(flags & 32) && g_tracking.g_tab_exec[1][i] == 'n' && (flags |= 32))
					hist_file_to_lst();
				if (!(flags & 64) && g_tracking.g_tab_exec[1][i] == 'p' && (flags |= 64))
					history_builtin_p();
				if (!(flags & 128) && g_tracking.g_tab_exec[1][i] == 's' && (flags |= 128) && ft_strchr(g_tracking.g_tab_exec[1], 'p') == NULL)
					history_builtin_s();
				i++;
			}
			i = 1;
}

void		history_builtin(void)
{
	// HISTFILE ENV VARIABLE TO ADD !!!!
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

// Setup the history list
// void		history_setup(void)
// {
// 			if (g_tracking.mysh->hist == NULL || g_tracking.mysh->hist->line == NULL)
// 				g_tracking.mysh->hist = hist_lst_create(g_tracking.->line);
// 			else
// 				hist_lst_add_next(g_tracking.mysh->hist, core->line);
// }