/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:06:32 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 19:25:25 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		shebang_word_plus(int i, char *line, char *nline, char *last_line)
{
	t_hist *hist;

	hist = g_tracking.mysh->hist;
	if ((!hist->previous && ft_strncmp(hist->line, line, i) != 0) || i == 0)
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (0);
	}
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return (1);
}

char	*shebang_word(char *line, char *last_line)
{
	char	*nline;
	int		i;
	t_hist	*hist;

	i = 0;
	hist = g_tracking.mysh->hist;
	if (!hist || (hist->line == NULL && hist->index != 0))
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (NULL);
	}
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	while (hist->previous && ft_strncmp(hist->line, line, i) != 0)
		hist = hist->previous;
	if (shebang_word_plus(i, line, nline, last_line) == 0)
	{
		free(nline);
		return (NULL);
	}
	return (nline);
}

int		shebang_num_pos_error(t_hist *hist)
{
	if (!hist || (hist->line == NULL && hist->line != 0))
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (0);
	}
	return (1);
}

int		shebang_num_pos_atoi(t_hist *hist, char *tmp, int i)
{
	if ((!hist->previous && hist->index != ft_atoi(tmp)) || i == 0 || i >= 5)
	{
		free(tmp);
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (0);
	}
	return (1);
}

char	*shebang_num_pos(char *line, char *last_line)
{
	char	*nline;
	char	*tmp;
	int		i;
	t_hist	*hist;

	i = 0;
	hist = g_tracking.mysh->hist;
	if (shebang_num_pos_error(hist) == 0)
		return (NULL);
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	tmp = ft_strrdup(line, i);
	while (hist->previous && hist->index != ft_atoi(tmp))
		hist = hist->previous;
	shebang_num_pos_atoi(hist, tmp, i);
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return (nline);
}
