/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/07 18:52:58 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*shebang_last(t_hist *hist, t_core *core, char *baseline, char *line, char *last_line)
{
	char *newline;

	core->hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	while (hist->next)
		hist = hist->next;
	newline = ft_memalloc(sizeof(char) * ft_strlen(last_line) + ft_strlen(hist->line) + ft_strlen(line) +1);
	newline = ft_strcpy(newline, last_line);
	newline = ft_strcat(newline, hist->line);
	newline = ft_strcat(newline, line);
	return newline;
}

char	*shebang_word(t_hist *hist, t_core *core, char *baseline, char *line, char *last_line)
{
	char *newline;
	int i;

	i = 0;
	core->hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	while (hist->previous && ft_strncmp(hist->line, line, i) != 0)
		hist = hist->previous;
	if (!hist->previous || i == 0 ||ft_strncmp(hist->line, line, i) != 0)
		{
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	newline = ft_memalloc(sizeof(char) * ft_strlen(last_line) + ft_strlen(hist->line) + ft_strlen(&line[i]) +1);
	newline = ft_strcpy(newline, last_line);
	newline = ft_strcat(newline, hist->line);
	newline = ft_strcat(newline, &line[i]);
	return newline;
}

char	*shebang_num_pos(t_hist *hist, t_core *core, char *baseline, char *line, char *last_line)
{
	char *newline;
	char *tmp;
	int i;

	i = 0;
	core->hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	while (hist->next)
		hist = hist->next;
	tmp = ft_strrdup(line, i);
	while (hist->previous && hist->index != ft_atoi(tmp))
		hist = hist->previous;
	if (!hist->previous || i == 0 || i <= 5 || hist->index != ft_atoi(tmp))
		{
			free(tmp);
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	newline = ft_memalloc(sizeof(char) * ft_strlen(last_line) + ft_strlen(hist->line) + ft_strlen(&line[i]) +1);
	newline = ft_strcpy(newline, last_line);
	newline = ft_strcat(newline, hist->line);
	newline = ft_strcat(newline, &line[i]);
	return newline;
}

char	*shebang_num_neg(t_hist *hist, t_core *core, char *baseline, char *line, char *last_line)
{
	char *newline;
	char *tmp;
	int i;

	i = 0;
	core->hist = hist_delete_last(hist);
	if (!hist || hist->line == NULL)
		{
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	while (line[i] && ft_isdigit(line[i]) && !ft_isspace(line[i]))
		i++;
	while (hist->previous)
		hist = hist->previous;
	tmp = ft_strrdup(line, i);
	while (hist->next && hist->index != ft_atoi(tmp))
		hist = hist->next;
	if (!hist->next || i == 0 || i <= 5 || hist->index != ft_atoi(tmp))
		{
			free(tmp);
			ft_putendl_fd("Event not found", 2);
			return baseline;
		}
	newline = ft_memalloc(sizeof(char) * ft_strlen(last_line) + ft_strlen(hist->line) + ft_strlen(&line[i]) +1);
	newline = ft_strcpy(newline, last_line);
	newline = ft_strcat(newline, hist->line);
	newline = ft_strcat(newline, &line[i]);
	return newline;
}

char 	*shebang_parse_switch(t_core *core, char *line)
{
	int 	i;
	char	*tmp_line;
	char	*show_line;

	i = 0;
	show_line = NULL;
	while (line && line[i])
	{
		if (line[i] && line[i] == '!')
		{
			i++;
			tmp_line = ft_strrdup(line, i-1);
			if (line[i] && line[i] == '!')
			{
				i++;
				line = shebang_last(core->hist, core, line, &line[i], tmp_line);
			}
			else if (line[i] && line[i] == '-')
			{
				i++;
				if (line[i] && ft_isdigit(line[i]))
					line = shebang_num_neg(core->hist, core, line, &line[i], tmp_line);
				else if (line[i])
					line = shebang_word(core->hist, core, line, &line[i], tmp_line);
			}
			else if (line[i] && ft_isdigit(line[i]))
				line = shebang_num_pos(core->hist, core, line, &line[i], tmp_line);
			else if (line[i] && !ft_isdigit(line[i]))
				line = shebang_word(core->hist, core, line, &line[i], tmp_line);
			free(tmp_line);
		}
		else
			i++;
	}
	if (tmp_line)
		free(tmp_line);
	show_line ? ft_putendl(show_line) : line;
	return line ;
}