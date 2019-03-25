/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:52:18 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/25 02:10:25 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		out_redir(t_last *list)
{
	int		fd;

	fd = 0;
	while (list && list->type != FICH)
		list = list->next;
	if ((fd = open(list->name, O_RDONLY)) == -1)
	{
		ft_putendl_fd("Couldn't open fich for out_redir", 2);
		dprintf(2, "STDIN = %d\n", g_tracking.mysh->set_fd->STDIN);
		dprintf(2, "STDOUT = %d\n", g_tracking.mysh->set_fd->STDOUT);
		dprintf(2, "STDERR = %d\n", g_tracking.mysh->set_fd->STDERR);
		return (-1);
	}
	return (fd);
}
