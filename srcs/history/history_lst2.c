/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:02:27 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/11 16:06:03 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save history into ~.shell_history
void		hist_save_file(t_core *core)
{
	int fd;


	fd = open("/goinfre/.shell_history", O_APPEND | O_CREAT, 0777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return;
	}
	while (core->hist->previous)
		core->hist = core->hist->previous;
	while(core->hist)
	{
		ft_putendl_fd(core->hist->line, fd);
		if (core->hist->next)
			core->hist = core->hist->next;
		else
			break;
	}
	close(fd);
}