/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/20 05:36:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

void		hist_to_file(int fd)
{
	t_list	*hist;

	hist = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!hist)
		return ;
	while (hist)
	{
		if (hist->content != NULL && ft_strlen(hist->content) > 0
		&& ft_strcmp(hist->content, "\n") != 0)
			ft_putendl_fd(hist->content, fd);
		hist = hist->next;
	}
}

void		hist_save_file(void)
{
	int		fd;
	char	*path;

	path = create_path_hist();
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 00777);
	if (fd < 0)
		return (ft_putendl_fd("Error while opening/creating .42hist", 2));
	hist_to_file(fd);
	ft_strdel(&path);
	close(fd);
	return ;
}
