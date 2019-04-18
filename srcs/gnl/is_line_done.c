/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_done.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:47:40 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/12 02:52:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "libft.h"

int		check_eol(char *line)
{
	int		i;
	char	**taab;

	i = 0;
	g_tracking.quotes = 0;
	if (g_tracking.interactive == 0)
		return (0);
	if (!line)
		return (0);
	taab = ft_split_whitespaces(line);
	if (taab)
	{
		while (taab[i])
			i++;
		i--;
		if (i > 0 && taab[i])
			if (ft_strcmp("&&", taab[i]) == 0 || ft_strcmp(taab[i], "||") == 0
			|| ft_strcmp(taab[i], "\\") == 0)
			{
				free_tab(taab);
				return (1);
			}
	}
	free_tab(taab);
	return (0);
}

char	*end_line(char *line)
{
	g_tracking.quotes = 3;
	get_key();
	line = ft_strjoinfree(line, g_tracking.cmd, 1);
	ft_free(g_tracking.cmd);
	g_tracking.cmd = NULL;
	ft_putchar('\n');
	return (line);
}
