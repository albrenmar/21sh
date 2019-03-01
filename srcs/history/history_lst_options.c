/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/01 17:20:23 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hist_file_to_lst(t_core *core)
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
	if (core->hist == NULL && get_next_line(fd, line) == 1)
		core->hist = hist_lst_create(*line);
	while (get_next_line(fd, line) == 1 && *line != NULL)
		hist_lst_add_next(core->hist, *line);
	close(fd);
	free(line);
}

// Save to file with w options
void		hist_save_file_w(t_hist *hist,char *path)
{
	int fd;
	char **line;

	if (!path)
		fd = open("/goinfre/.shell_history", O_WRONLY | O_CREAT  | O_TRUNC, 00777);
	else
		fd = open(path, O_WRONLY | O_CREAT  | O_TRUNC, 00777);
	if (fd < 0)
	{
		ft_putendl_fd("Error while opening/creating .shell_history", 2);
		return;
	}
	if (!hist)
	{
		close(fd);
		return;
	}
	while (hist->previous)
		hist = hist->previous;
	while(hist)
	{
		ft_putendl_fd(hist->line, fd);
		if (hist->next)
			hist = hist->next;
		else
			break;
	}
	lseek(fd, SEEK_SET, 0);
	line = malloc(sizeof(line));
	while(get_next_line(fd, line) == 1)
		ft_putendl(*line);
	free(line);
	close(fd);

}

void		history_builtin_digit(t_core *core)
{
	int num;

	num = ft_atoi(core->arg[1]);
		while (core->hist->next)
			core->hist = core->hist->next;
		if (ft_strlen(core->arg[1]) >= 8)
		{
			hist_print(core->hist);
			return ;
		}
		while (num > 0 && core->hist)
		{
			ft_putnbr(core->hist->index);
			ft_putchar(' ');
			ft_putendl(core->hist->line);
			core->hist = core->hist->previous;
			num--;
		}
}

void		history_builtin_p(t_core *core)
{
	int i;
	int j;
	// char *tmp;

	i = 1;
	j = 2;
	if (core->arg[j] == NULL)
		return ;
	if (ft_strchr(core->arg[1], 's'))
	{
		history_builtin_s(core);
		return ;
	}
	else
	{
		while (core->arg[j])
		ft_putendl(core->arg[j++]);
		if (core->hist)
			core->hist = hist_delete_last(core->hist);
	}
}
// Faire s'execute avec des !command (shebang)
// Prend la derniere commannde a partir de la fin
// Sinon comportement normal