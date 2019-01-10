/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:26:34 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:30:16 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_echo_n(t_core *core)
{
	int			i;

	i = 2;
	while (core->arg[i])
	{
		ft_putstr(core->arg[i]);
		(core->arg[i + 1]) ? ft_putchar(' ') : 0;
		i++;
	}
}

static void		ft_echo(t_core *core)
{
	int			i;

	i = 1;
	while (core->arg[i])
	{
		ft_putstr(core->arg[i]);
		(core->arg[i + 1]) ? ft_putchar(' ') : ft_putstr("\n");
		i++;
	}
}

void			echo_builtin(t_core *core)
{
	if (!core->arg[1])
		ft_putchar('\n');
	else if (!core->arg[2] && ft_strcmp(core->arg[1], "-n") == 0)
		return ;
	else if (ft_strcmp(core->arg[1], "-n") == 0)
		ft_echo_n(core);
	else
		ft_echo(core);
}
