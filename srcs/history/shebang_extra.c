/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:25:33 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 16:15:12 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	shebang_num_neg_line(int i, char *line, char *nline, char *last_line)
{
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, g_tracking.mysh->hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
}

int		shebang_num_neg_check(int i, char *tmp)
{
	if ((!g_tracking.mysh->hist->next\
	&& g_tracking.mysh->hist->index != ft_atoi(tmp)) || i == 0 || i >= 5)
	{
		free(tmp);
		ft_putendl_fd("Event not found", 2);
		return (0);
	}
	return (1);
}

int		shebang_num_neg_event_error(void)
{
	if (!g_tracking.mysh->hist || g_tracking.mysh->hist->line == NULL)
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (0);
	}
	return (1);
}

char	*shebang_num_neg(char *line, char *last_line)
{
	char	*nline;
	char	*tmp;
	int		i;
	t_hist	*hist;

	hist = get_hist_nbr(1);
	i = 0;
	if (shebang_num_neg_event_error() == 0)
		return (NULL);
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	tmp = ft_strrdup(line, i);
	while (hist->next)
	{
		if (hist->index != ft_atoi(tmp))
			hist = hist->next;
		else
			break ;
	}
	if (shebang_num_neg_check(i, tmp) == 0)
		return (NULL);
	shebang_num_neg_line(i, line, nline, last_line);
	return (nline);
}
