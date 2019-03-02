/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/02 06:21:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh42.h>

char	*create_path_hist(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 3);// ORIGINAL
//	path = ft_strjoinfree(path, user, 1);// MJOSE LINUX
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
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = hist_lst_create(*line);
	while (get_next_line(fd, line) == 1 && *line != NULL)
		hist_lst_add_next(g_tracking.mysh->hist, *line);
	close(fd);
	free(path);
	free(line);
}
