/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 01:52:42 by mjose             #+#    #+#             */
/*   Updated: 2019/03/09 05:13:24 by mjose            ###   ########.fr       */
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

void	unquote(char **value, int *quote)
{
	char	*scan;
	int		type;

	scan = *value;
	type = *quote;
	if (*scan == '\'')
	{
		if (type != '"')
		{
			scan++;
			type = '\'';
		}
	}
	else if (*scan == '"')
	{
		if (type != '\'')
		{
			scan++;
			type = '"';
		}
	}
	*value = scan;
	*quote = type;
}

int		quote_error(char *scan, int open_key, int quote)
{

	if (quote && open_key && ft_iswhitespace(*scan))
		return ('E');
	else if (*scan == '{' && ft_iswhitespace(*(scan + 1)))
		return ('E');
	return (0);
}

void	reassign_value(char **value, char *new_value, int quote)
{
	if (quote != 'E')
	{
		ft_strdel(value);
		*value = new_value;
	}
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
		unquote(&scan, &quote);
		if (*scan == '{' && !ft_iswhitespace(*(scan + 1)))
			open_key++;
		else if (open_key == 1 && *scan == '}')
			open_key = 0;
		else if ((quote = quote_error(scan, open_key, quote)))
			break ;
		if (*scan != '"' && *scan != '\'')
			new_value[i++] = *scan;
		if (*scan)
			scan++;
	}
	reassign_value(value, new_value, quote);
	return (quote);
}
