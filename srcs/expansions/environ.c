/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 05:36:36 by mjose             #+#    #+#             */
/*   Updated: 2019/02/19 05:34:27 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		have_envname(char *var)
{
	t_list		*env;
	t_keyval	*buf;
	t_env_set	*set_env;

	if (g_tracking.mysh->env != NULL)
	{
		env = g_tracking.mysh->env->firstelement;
		while (env)
		{
			buf = env->content;
			if (ft_strcmp(var, buf->key) == 0)
				return (1);
			if (env->next)
				env = env->next;
			else
				break ;
		}
	}
	if (g_tracking.mysh->setenv_lst == NULL)
		return (0);
	set_env = g_tracking.mysh->setenv_lst;
	while (set_env)
	{
		buf = set_env->param;
		if (ft_strcmp(var, buf->key) == 0)
			return (2);
		if (set_env->next)
			set_env = set_env->next;
		else
			return (0);
	}
	return (0);
}
