/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:25:33 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 19:46:24 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		shebang_num_neg_check(t_hist *hist)
{
	if (!hist || hist->line == NULL)
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (0);
	}
	return (1);
}

int		shebang_num_neg_atoi(t_hist *hist, char *tmp, int i)
{
	if ((!hist->next && hist->index != ft_atoi(tmp)) || i == 0 || i >= 5)
	{
		free(tmp);
		ft_putendl_fd("Event not found", 2);
		return (0);
	}
	return (1);
}

t_hist	*iterate_hist(t_hist *hist, char *tmp)
{
	while (hist->next)
	{
		if (hist->index != ft_atoi(tmp))
			hist = hist->next;
		else
			break ;
	}
	return (hist);
}

char	*shebang_num_neg(char *line, char *last_line)
{
	char	*nline;
	char	*tmp;
	int		i;
	t_hist	*hist;

	hist = get_hist_nbr(1);
	i = 0;
	if (shebang_num_neg_check(hist) == 0)
		return (NULL);
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	tmp = ft_strrdup(line, i);
	hist = iterate_hist(hist, tmp);
	if (shebang_num_neg_atoi(hist, tmp, i) == 0)
		return (NULL);
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return (nline);
}
