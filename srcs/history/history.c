/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/21 16:30:02 by hdufer           ###   ########.fr       */
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

// Dispatch the action and do the history builtin
void		history_builtin(t_core *core)
{
	int i = 0;
	char flags = 0;

	if (core->arg[1] == NULL)
		hist_print(core->hist);
	else
	{
		if (core->arg[1][0] == '-')
		{
			while (core->arg[1][i])
			{
				if (!(flags & 1) && core->arg[1][i] == 'c' && (flags |= 1))
					core->hist = hist_free(core->hist);
				// BUG WHEN -CDXXXXX 
				if (!(flags & 2) && core->arg[1][i] == 'd' && (flags |= 2))
					history_builtin_delete_index(core, i);
				if (!(flags & 4) && core->arg[1][i] == 'a' && (flags |= 4))
					hist_save_file(core->hist);
				if (!(flags & 8) && core->arg[1][i] == 'r' && (flags |= 8))
					hist_file_to_lst(core);
				if (!(flags & 16) && core->arg[1][i] == 'w' && (flags |= 16))
					hist_save_file(core->hist);
				i++;
			}
			i = 1;
		}
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