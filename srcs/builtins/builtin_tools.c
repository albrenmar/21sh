/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/28 06:29:40 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			builtin_exec_cont_2(void)
{
	if (ft_builtin_search("true"))
		return (0);
	else if (ft_builtin_search("false"))
		return (1);
	return (0);
}

int			cd_args_len(void)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = g_tracking.g_tab_exec;
	while (tmp[i])
		i++;
	return (i);
}
