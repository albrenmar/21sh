/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 00:06:02 by mjose            ###   ########.fr       */
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

int		tab_exec_arg(char ***tab_exec, char ***tab_farg, int i_arg, int i)
{
	char	**run_texec;
	char	**run_tfarg;

	run_texec = *tab_exec;
	run_tfarg = *tab_farg;
	free_tab(run_texec);
	run_texec = ft_memalloc(sizeof(char *) * (i + i_arg + 1));
	i_arg = 0;
	while (run_tfarg[i_arg])
	{
		run_texec[i_arg] = ft_strdup(run_tfarg[i_arg]);
		i_arg++;
	}
	*tab_exec = run_texec;
	return (i_arg);
}
