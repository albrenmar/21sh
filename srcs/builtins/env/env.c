/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 03:49:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			ft_env(int i, int count)
{
	char		**exec;
	t_list		*hold;
	t_keyval	*tmp;

	hold = NULL;
	if (g_tracking.mysh->env)
		hold = g_tracking.mysh->env->firstelement;
	exec = g_tracking.g_tab_exec;
	while (exec[i++])
		count++;
	if (count == 1)
	{
		while (hold)
		{
			tmp = hold->content;
			ft_putstr(tmp->key);
			ft_putchar('=');
			ft_putendl(tmp->value);
			hold = hold->next;
		}
		return (0);
	}
	ft_putstr_fd(SHELL_NAME": env: ", 2);
	ft_putendl_fd("only takes arguments with options: [-i]", 2);
	return (1);
}
