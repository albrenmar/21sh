/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 05:36:36 by mjose             #+#    #+#             */
/*   Updated: 2019/02/16 06:24:30 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		have_envname(char *var)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->env == NULL)
		return (0);
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(var, buf->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
