/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:43:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/18 17:46:19 by hdufer           ###   ########.fr       */
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
		core->hist = hist_delete_last(core->hist);
	i = 0;
	ft_putendl(builtin_s_args(core->arg));
}