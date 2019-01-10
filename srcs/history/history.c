/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:53:06 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/10 14:54:35 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		history_builtin(t_core *core)
{
	if ()
}
// Setup the history list
void		history_setup(t_core *core)
{
			if (core->hist == NULL && core->line != NULL)
				core->hist = hist_lst_create(core);
			else
				hist_lst_add_next(core);
			hist_print(core);
}