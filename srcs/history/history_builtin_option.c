/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:43:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/01 19:05:15 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	history_builtin_s(t_core *core)
{
	int i;
	int j;
	int h;

	i = 2;
	j = 0;
	h = 0;
	if (!(core->arg[i]))
		return ;
	else
		if (core->hist)
			core->hist = hist_delete_last(core->hist);
	core->hist = builtin_s_args(&core->arg[i], core->hist);
}