/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_general.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:32:39 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 16:21:48 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		hist_save_file(t_hist *hist)
{
	int		fd;
	char	*path;

	path = create_path_hist();
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 00777);
	if (fd < 0)
		return (ft_putendl_fd("Error while opening/creating .42hist", 2));
	if (!hist)
	{
		close(fd);
		return ;
	}
	while (hist->previous)
		hist = hist->previous;
	while (hist)
	{
		if (hist->line != NULL && ft_strlen(hist->line) > 0)
			ft_putendl_fd(hist->line, fd);
		hist = hist->next;
	}
	free(path);
	close(fd);
}

void		history_builtin_delete_index_return(int j, char *tmp, int i[2])
{
	char *error;

	error = "history -d require valid argument:history -d [digit]";
	if (!(g_tracking.g_tab_exec[1][j + 1]) && !(g_tracking.g_tab_exec[2]))
		return (ft_putendl_fd(error, 2));
	if (ft_isdigit(g_tracking.g_tab_exec[1][j + 1]))
	{
		j++;
		while (g_tracking.g_tab_exec[1][j])
		{
			if (ft_isdigit(g_tracking.g_tab_exec[1][j]) && j <= 100000)
			{
				tmp[i[0]] = g_tracking.g_tab_exec[1][j++];
				i[0]++;
			}
			else
			{
				ft_putendl_fd("history position out of range", 2);
				return ;
			}
		}
	}
	if (g_tracking.mysh->hist)
		g_tracking.mysh->hist = hist_delete_index(g_tracking.mysh->hist,\
		ft_atoi(tmp));
}

void		history_builtin_delete_index_check(int j, char *tmp, int i[2])
{
	if (ft_isdigit(g_tracking.g_tab_exec[2][i[1]]))
	{
		while (g_tracking.g_tab_exec[2][i[1]])
		{
			if (ft_isdigit(g_tracking.g_tab_exec[2][i[1]]) \
			&& i[1] <= 100000)
			{
				tmp[i[0]] = g_tracking.g_tab_exec[2][i[1]];
				i[1]++;
				j++;
			}
			else
			{
				ft_putendl_fd("history position out of range", 2);
				return ;
			}
		}
	}
	else
		return (ft_putendl_fd("history position out of range", 2));
}

void		history_builtin_delete_index(int j)
{
	char	tmp[100000];
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	if (!(g_tracking.g_tab_exec[1][j + 1]) && (g_tracking.g_tab_exec[2]))
		history_builtin_delete_index_check(j, tmp, &i[2]);
	history_builtin_delete_index_return(j, tmp, &i[2]);
}
