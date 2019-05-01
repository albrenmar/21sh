/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 07:16:59 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**convert_backtab(char **taab)
{
	int		i;

	i = 0;
	while (taab[i])
	{
		taab[i] = convert_back(taab[i]);
		taab[i] = remove_back(taab[i], 0);
		i++;
	}
	return (taab);
}

int		tab_exec_arg(char **tab_exec, char **tab_farg, int i_arg, int i)
{
	free_tab(tab_exec);
	tab_exec = ft_memalloc(sizeof(char *) * (i + i_arg + 1));
	i_arg = 0;
	while (tab_farg[i_arg])
	{
		tab_exec[i_arg] = ft_strdup(tab_farg[i_arg]);
		i_arg++;
	}
	return (i_arg);
}
