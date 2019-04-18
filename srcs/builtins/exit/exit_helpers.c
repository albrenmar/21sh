/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 01:49:55 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		free_remains(void)
{
	ft_free(g_tracking.pos);
	ft_free(g_tracking.cpaste->line);
	ft_free(g_tracking.cpaste);
	reset_tmpenv();
	reset_resetenv();
	ft_free(g_tracking.mysh);
}

void		free_and_null(void *ptr)
{
	if (ptr)
	{
		ft_free(ptr);
		ptr = NULL;
	}
}

int			ft_exit3(int exitcode, int mode)
{
	free_mysh();
	clean_up_leaks();
	clean_up_leaks();
	empty_hash_table();
	free_all_jobs();
	if (g_tracking.mysh->envsave != NULL)
		next_cmd_update();
	if (mode == 2)
		free_remains();
	if (GARBAGE == 1)
		free_all_list();
	exit(exitcode);
}
