/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int				is_spaces(char *str, int i, int mode)
{
	if (mode == 1)
	{
		if (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == ' '))
			return (1);
	}
	else if (mode == 2)
	{
		if (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == ' ' || str[i] == ';'
		|| str[i] == '&' || str[i] == '|'))
			return (1);
	}
	else if (mode == 3)
	{
		if (str[i] && (str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == ' '
		|| str[i] == ';' || str[i] == '&' || (str[i] == '|'
		&& str[i - 1] && str[i - 1] == '|')))
			return (1);
	}
	return (0);
}

int				next_separator(char *str, int i)
{
	while (i < (int)ft_strlen(str))
	{
		if ((str[i] == '&' && str[i + 1] && (str[i + 1] == '&'
		|| is_spaces(str, i + 1, 1))) || str[i] == '|' || str[i] == ';')
		{
			while (str[i] == '&' || str[i] == '|' || str[i] == ';')
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

void			swap_alias_helper(char *new, int l, int i, char *str)
{
	while (str[l] != '\0')
	{
		new[i] = str[l];
		i++;
		l++;
	}
	new[i] = '\0';
}

char			*swap_alias(char *str, int j, int isave, t_keyval *tmp)
{
	char		*new;
	int			len;
	int			i;
	int			l;

	len = ft_strlen(str) - j + ft_strlen(tmp->value);
	if (!(new = ft_malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	l = 0;
	while (str[i] && i < isave)
	{
		new[i] = str[i];
		i++;
	}
	while (tmp->value[l] != '\0')
	{
		new[i] = tmp->value[l];
		i++;
		l++;
	}
	l = i - l + j;
	swap_alias_helper(new, l, i, str);
	ft_strdel(&str);
	return (new);
}
