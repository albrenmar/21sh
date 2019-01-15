/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/15 14:34:47 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dispatch the action and do the history builtin
void		history_builtin(t_core *core)
{
	int i;
	i = 1;
	if (core->arg[1] == NULL)
		hist_print(core->hist);
	else
	{
		if (core->arg[1][0] == '-')
		{
			while (core->arg[1][i])
			{
				if (core->arg[1][i] == 'c')
				{
					ft_putendl("Let's clear this");
					core->hist = hist_free(core->hist);
				}
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