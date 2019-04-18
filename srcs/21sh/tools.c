/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 01:47:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	free_tabs_and_exit(char **envhold, char **tab_exec_hold)
{
	free_tab(envhold);
	free_tab(tab_exec_hold);
	ft_exit3(EXIT_FAILURE, 2);
}

int		spaces_line_check(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t'
				&& line[i] != '\v' && line[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

char	**tab_dup(char **tob)
{
	int			i;
	char		**new;

	i = 0;
	new = NULL;
	while (tob[i])
		i++;
	if (!(new = ft_malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tob[i])
	{
		new[i] = ft_strdup(tob[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
