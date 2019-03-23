/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/23 18:56:11 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*shebang_last(char *line, char *last_line)
{
	char	*nline;
	t_hist	*hist;
	int		i;

	i = 0;
	hist = g_tracking.mysh->hist;
	if (!hist || hist->line == NULL)
	{
		ft_putendl_fd("Event not found", 2);
		g_tracking.shebang = 1;
		return (NULL);
	}
	while (hist->next)
		hist = hist->next;
	nline = ft_strdup(last_line);
	nline = ft_strjoinfree(nline, hist->line, 1);
	nline = ft_strjoinfree(nline, &line[i], 1);
	g_tracking.shebang = 2;
	return (nline);
}

void	shebang_parse_switch_plus(char *line, int i, char *tmp_line)
{
	if (line[i] && line[i] == '!')
	{
		i++;
		line = shebang_last(&line[i], tmp_line);
		i = 0;
	}
	else if (line[i] && line[i] == '-')
	{
		i++;
		if (line[i] && ft_isdigit(line[i]))
			line = shebang_num_neg(&line[i], tmp_line);
		else if (line[i])
			line = shebang_word(&line[i], tmp_line);
		i = 0;
	}
	else if (line[i] && ft_isdigit(line[i]))
	{
		line = shebang_num_pos(&line[i], tmp_line);
		i = 0;
	}
	else if (line[i] && !ft_isdigit(line[i]))
	{
		line = shebang_word(&line[i], tmp_line);
		i = 0;
	}
}

char	*shebang_parse_switch(char *line)
{
	int		i;
	char	*tmp_line;

	i = 0;
	g_tracking.shebang = 0;
	while (g_tracking.shebang != 1 && line && line[i])
	{
		if (line[i] && line[i] == '!')
		{
			i++;
			tmp_line = ft_strrdup(line, i - 1);
			if (ft_iswhitespace(line[i]) || !line[i] || line[i] == ';')
				i++;
			else
			{
				shebang_parse_switch_plus(line, i, tmp_line);
				i = 0;
			}
			free(tmp_line);
		}
		else
			i++;
	}
	line && g_tracking.shebang == 2 ? ft_putendl(line) : NULL;
	return (line);
}
