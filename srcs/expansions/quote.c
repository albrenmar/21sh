/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 01:52:42 by mjose             #+#    #+#             */
/*   Updated: 2019/03/23 05:38:53 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int			ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
					|| c == '\r')
		return (1);
	return (0);
}

void		unquote(char **value, int *quote)
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

int			quote_error(char *scan, int open_key, int quote)
{
	if (quote && open_key && ft_iswhitespace(*scan))
		return ('E');
	else if (*scan == '{' && ft_iswhitespace(*(scan + 1)))
		return ('E');
	return (quote);
}

void		reassign_value(char **value, char *new_value, int quote)
{
	if (quote != 'E')
	{
		ft_strdel(value);
		*value = new_value;
	}
}

t_unquoter	*unquote_value(char **value)
{
	char		*scan;
	t_unquoter	*to_unquot;
	t_unquoter	*first;
	char		next_quote;

	scan = *value;
	to_unquot = new_unquoted_value();
	to_unquot->error = 0;
	first = to_unquot;
	while (*scan)
	{
		to_unquot = quote_checker(to_unquot, &scan);
		if (*scan && *scan + 1)
		{
			next_quote = to_unquot->next->type;
			if (next_quote < 0)
				next_quote = '\0';
			to_unquot->next = new_unquoted_value();
			to_unquot = to_unquot->next;
			to_unquot->type = next_quote;
		}
	}
	return (first);
}
