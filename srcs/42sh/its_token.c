/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 04:18:28 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/08 02:29:05 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		its_reddir_to_fd(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '>' && list->name[i + 1] && list->name[i + 1] == '&')
		return (1);
	return (0);
}

int		its_fd_reddir(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '>')
		return (1);
	return (0);
}

int		its_eper(t_last *list)
{
	int		i;

	i = 0;
	if (list && list->name[i] && ft_strlen(list->name) == 1 && list->name[i] == '&')
		return (1);
	return (0);
}

int		its_reddir(t_last *list)
{
	int		i;

	i = 0;
	if (list->name[i] && list->name[i] == '>')
		return (1);
	return (0);
}

int		its_pipe(t_last *list)
{
	int		i;

	i = 0;
	if (list && list->name[i] && ft_strlen(list->name) == 1 && list->name[i] == '|')
		return (1);
	return (0);
}

char	*its_quote(int i, char *str, int *nb, char c)
{
	char	*temp;

	temp = NULL;
	i++;
	while (str[i] && str[i] != c)
		i++;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '&' && str[i] != '>' && str[i] != '<')
		i++;
	(*nb) += i;
	temp = ft_strndup(str, i);
	return (temp);
}

int		its_separator(t_last *list)
{
	if (ft_strlen(list->name) == 2)
	{
		if (list->name[0] == '|' || list->name[0] == '&')
			return (1);
	}
	else if (list->name[0] == ';')
		return (1);
	return (0);
}
