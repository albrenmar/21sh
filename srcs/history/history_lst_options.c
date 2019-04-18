/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/04/14 23:25:35 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*create_path_hist(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 1);
	path = ft_strjoinfree(path, "/.42hist", 1);
	return (path);
}

void	hist_file_to_lst(void)
{
	int		fd;
	char	*line;
	char	*path;
	int		t;

	line = NULL;
	path = create_path_hist();
	fd = open(path, O_CREAT | O_RDWR, 00777);
	ft_free(path);
	if (fd < 0)
		ft_putendl_fd("Error while opening/creating .42hist", 2);
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = hist_lst_create(NULL);
	while ((t = get_next_line(fd, &line)) == 1 && line != NULL)
	{
		if (ft_strcmp(line, "\n") != 0)
			hist_lst_add_next(g_tracking.mysh->hist, line);
		if (line)
			ft_free(line);
		line = NULL;
	}
	ft_free(line);
	line = NULL;
	close(fd);
}

void	hist_print_test(t_hist *hist, int i)
{
	if (hist->line)
	{
		while (i-- > 0)
			ft_putchar(' ');
		ft_putnbr(hist->index);
		ft_putchar(' ');
		ft_putendl(hist->line);
	}
}
