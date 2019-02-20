/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fich.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:24:49 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 14:26:22 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		create_fich(t_last *list)
{
	int		i;
	int		fd_fich;

	i = 0;
	fd_fich = 0;
	if (its_reddir(list))
	{
		while (list->type != FICH)
			list = list->next;
		g_tracking.mysh->set_fd->STDOUT = open(list->name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else if (its_fd_reddir(list))
	{
		while (list->name[i] > 47 && list->name[i] < 58)
		{
			i++;
		}
		while (list->type != FICH)
			list = list->next;
		fd_fich = open(list->name, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (i < 2)
		{
			if (list->name[0] == '0')
				g_tracking.mysh->set_fd->STDIN = fd_fich;
			else if (list->name[0] == '1')
				g_tracking.mysh->set_fd->STDOUT = fd_fich;
			else if (list->name[0] == '2')
				g_tracking.mysh->set_fd->STDERR = fd_fich;
		}
	}
}
