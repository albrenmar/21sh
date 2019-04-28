/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 04:53:50 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/28 23:01:28 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*int		ft_basic_bracket(char *line, char c, int flag)
{
	int		i;

	i = 0;
	if (!line)
		return (2);
	while (line[i])
	{
		if (line[i] == c && flag == 0)
		{
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (!line[i])
				return (0);
		}
		else if ((line[i] == c && is_escape(line, i) != 1) && !flag)
			flag++;
		else if ((line[i] == c && is_escape(line, i) != 1) && flag)
			flag--;
		i++;
	}
	return (flag == 0 ? 0 : 1);
}*/

int			check_basic_quotes(char *line)
{
	int		flag;

	flag = 0;
	if (ft_valid_quote(line, '\'', 0) != 0)
		flag++;
	if (ft_valid_quote(line, '\"', 0) != 0)
		flag++;
	if (ft_valid_bracket(line) != 0)
		flag++;
	return (flag);
}

void		basic_mode(void)
{
	char	*str;

	str = NULL;
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	get_next_line(0, &str);
	if (check_basic_quotes(str) == 0)
		g_tracking.cmd = ft_strdup(str);
	else
	{
		ft_putstr_fd("Missing quotes in cmd:", 2);
		ft_putendl_fd(str, 2);
		g_tracking.cmd = NULL;
	}
	g_tracking.str = NULL;
	ft_strdel(&str);
}
