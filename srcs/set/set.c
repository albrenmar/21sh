/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:26:41 by mjose             #+#    #+#             */
/*   Updated: 2019/02/25 06:11:28 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		show_setenv(void)
{
	t_env_set	*set_var;

	set_var = NULL;
	ft_printlist();
	if (g_tracking.mysh->setenv_lst)
		set_var = g_tracking.mysh->setenv_lst;
	while (set_var && set_var->param)
	{
		ft_putstr(set_var->param->key);
		ft_putchar('=');
		ft_putendl(set_var->param->value);
		set_var = set_var->next;
	}
	return (0);
}
