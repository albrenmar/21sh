/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 08:40:37 by mjose             #+#    #+#             */
/*   Updated: 2019/02/17 10:37:57 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

t_env_set	*new_envset(char *varname, char *varvalue)
{
	t_env_set	*env_lst;
	t_keyval	*buf;

	buf = (t_keyval *)malloc(sizeof(t_keyval));
	env_lst = (t_env_set *)malloc(sizeof(t_env_set));
	buf->key = varname;
	buf->value = varvalue;
	env_lst->param = buf;
	env_lst->next = NULL;

	return (env_lst);
}

void	add_to_env_set(char *varname, char *varvalue)
{
	t_env_set	*env_list;
	t_env_set	*first;

	if (g_tracking.mysh->setenv_lst == NULL)
		g_tracking.mysh->setenv_lst = new_envset(varname, varvalue);
	else
	{
		env_list = g_tracking.mysh->setenv_lst;
		first = g_tracking.mysh->setenv_lst;
		while (env_list)
			env_list = env_list->next;
		env_list = new_envset(varname, varvalue);
	}
}