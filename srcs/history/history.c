/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/01 15:01:57 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// history builtin for delete index option
void		history_builtin_delete_index(t_core *core, int j)
{
	char tmp[100000];
	int i[2];
	i[0] = 0;
	i[1] = 0;
	if (!(core->arg[1][j+1]) && (core->arg[2]))
	{
		if (ft_isdigit(core->arg[2][i[1]]))
		{
			while (core->arg[2][i[1]])
			{
				if (ft_isdigit(core->arg[2][i[1]]) && i[1] <= 100000)
				{
					tmp[i[0]] = core->arg[2][i[1]];
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
	else if (!(core->arg[1][j+1]) && !(core->arg[2]))
	{
		ft_putendl_fd("history -d require valid argument: history -d [digit]",2);
		return;
	}
	else if (ft_isdigit(core->arg[1][j+1]))
	{
		j++;
		while (core->arg[1][j])
		{
			if (ft_isdigit(core->arg[1][j]) && j <= 100000)
			{
				tmp[i[0]] = core->arg[1][j];
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
	if (core->hist)
		core->hist = hist_delete_index(core->hist, ft_atoi(tmp));
}

void		history_builtin_minus(t_core *core)
{
	int i;
	char flags;

	i = 1;
	flags = 0;
	while (core->arg[1][i])
			{
				if (ERROR_FLAGS_HIST)
				{
					ft_putendl_fd("history -[ardcwnps]", 2);
					return;
				}
				if (!(flags & 1) && core->arg[1][i] == 'c' && (flags |= 1))
					core->hist = hist_free(core->hist);
				if (!(flags & 2) && core->arg[1][i] == 'd' && (flags |= 2))
					history_builtin_delete_index(core, i);
				if (!(flags & 4) && core->arg[1][i] == 'a' && (flags |= 4))
					hist_save_file(core->hist);
				if (!(flags & 8) && core->arg[1][i] == 'r' && (flags |= 8))
					hist_file_to_lst(core);
				if (!(flags & 16) && core->arg[1][i] == 'w' && (flags |= 16))
					hist_save_file_w(core->hist, core->arg[2]);
				if (!(flags & 32) && core->arg[1][i] == 'n' && (flags |= 32))
					hist_file_to_lst(core);
				if (!(flags & 64) && core->arg[1][i] == 'p' && (flags |= 64))
					history_builtin_p(core);
				i++;
			}
			i = 1;
}

// Dispatch the action and do the history builtin
void		history_builtin(t_core *core)
{
	// HISTFILE ENV VARIABLE TO ADD !!!!
	if (core->arg[1] == NULL)
		hist_print(core->hist);
	else
	{
		if (core->arg[1][0] == '-')
			history_builtin_minus(core);
		else if (ft_isdigit_str(core->arg[1]))
			history_builtin_digit(core);
		else
			ft_putendl_fd("history argument need to be digit", 2);
	}
}

// Setup the history list
void		history_setup(t_core *core)
{
	if (core->hist == NULL || core->hist->line == NULL)
		core->hist = hist_lst_create(core->line);
	else
		hist_lst_add_next(core->hist, core->line);
}