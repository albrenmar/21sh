/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 01:52:42 by mjose             #+#    #+#             */
/*   Updated: 2019/03/03 11:31:56 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
					|| c == '\r')
		return (1);
	return (0);
}

char	unquote_value(char **value, int quote)
{
	char	*new_value;
	char	*scan;
	int		i;
	int		open_key;

	scan = ft_strdup(*value);
	new_value = ft_strnew(ft_strlen(*value));
	i = 0;
	open_key = 0;
	while (*scan != '\0')
	{
		if (*scan == '\'')
		{
			if (quote != '"')
			{
				scan++;
				quote = '\'';
			}
		}
		else if (*scan == '"')
		{
			if (quote != '\'')
			{
				scan++;
				quote = '"';
			}
		}
		if (*scan == '{' && !ft_iswhitespace(*(scan + 1)))
			open_key++;
		else if (open_key == 1 && *scan == '}')
			open_key = 0;
		else if (quote && open_key && ft_iswhitespace(*scan))
		{
			quote = 'E';
			break ;
		}
		else if (*scan == '{' && ft_iswhitespace(*(scan + 1)))
		{
			quote = 'E';
			break ;
		}
		new_value[i++] = *scan;
		if (*scan)
			scan++;
	}
	if (quote != 'E')
	{
		ft_strdel(value);
		*value = new_value;
	}
	return (quote);
}
