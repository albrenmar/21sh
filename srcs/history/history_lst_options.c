/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/15 04:43:50 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

char	*create_path_hist(void)
{
	char	*path;

	path = ft_strdup("/Users/");
	path = ft_strjoinfree(path, USER, 1);
	path = ft_strjoinfree(path, "/.42shist", 1);
	return (path);
}

void	hist_file_to_lst(void)
{
	int		fd;
	char	**line;
	char	*path;

	line = ft_memalloc(sizeof(line));
	path = create_path_hist();
	fd = open(path, O_CREAT | O_APPEND | O_RDWR, 00777);
	if (fd < 0)
		ft_putendl("Error while opening/creating .shell_history");
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = hist_lst_create(*line);
	while (get_next_line(fd, line) == 1 && *line != NULL)
		hist_lst_add_next(g_tracking.mysh->hist, *line);
	close(fd);
	free(line);
}
