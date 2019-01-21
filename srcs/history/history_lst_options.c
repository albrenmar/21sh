/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/21 17:26:31 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

void	hist_file_to_lst(void)
{
	int fd;
	char **line;

	line = ft_memalloc(sizeof(line));
	fd = open("/goinfre/.shell_history", O_CREAT | O_APPEND | O_RDWR, 00777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return;
	}
	if (g_tracking.mysh->hist == NULL && get_next_line(fd, line) == 1)
		g_tracking.mysh->hist = hist_lst_create(*line);
	while (get_next_line(fd, line) == 1 && *line != NULL)
		hist_lst_add_next(g_tracking.mysh->hist, *line);
	close(fd);
	free(line);
}
