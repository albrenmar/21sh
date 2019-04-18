/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "environ.h"

int			ft_unset(void)
{
	char	**taab;
	int		i;

	taab = g_tracking.g_tab_exec;
	i = 1;
	while (taab[i])
		remove_env_string(taab[i++]);
	i = 1;
	while (taab[i])
		remove_set_env_string(taab[i++]);
	return (0);
}
