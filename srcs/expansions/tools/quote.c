/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 01:52:42 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:56:38 by mjose            ###   ########.fr       */
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

t_unquoter	*remove_quote_data(t_unquoter *to_unquot, char next_quote)
{
	free(&to_unquot->next->str_unquoted);
	to_unquot->next = NULL;
	to_unquot->next = new_unquoted_value();
	to_unquot->next->type = next_quote;
	to_unquot = to_unquot->next;
	return (to_unquot);
}

void		re_quote(t_unquoter *to_unquot, char *scan)
{
	if (*scan)
	{
		ft_strdel(&to_unquot->next->str_unquoted);
		free(to_unquot->next);
		to_unquot->next = NULL;
		to_unquot->next = new_unquoted_value();
		if (to_unquot->str_unquoted[ft_strlen(to_unquot->str_unquoted)] == '\'')
		{
			to_unquot->str_unquoted[ft_strlen(to_unquot->str_unquoted)] = '\0';
			to_unquot->next->str_unquoted = ft_strjoinfree("\'", scan, 0);
		}
		else
			to_unquot->next->str_unquoted = ft_strdup(scan);
		to_unquot->next->type = '\'';
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
			if (to_unquot->next && next_quote)
				to_unquot = remove_quote_data(to_unquot, next_quote);
			else
				break ;
		}
	}
	re_quote(to_unquot, scan);
	return (first);
}

void		quotenize(t_unquoter *first, char **value)
{
	t_unquoter	*to_quot;

	to_quot = first;
	ft_strdel(value);
	*value = ft_strnew(1);
	while (to_quot)
	{
		if (to_quot->type)
		{
			*value = ft_strjoinchar(*value, to_quot->type, 1);
			*value = ft_strjoinfree(*value, to_quot->str_unquoted, 1);
			*value = ft_strjoinchar(*value, to_quot->type, 1);
		}
		else
			*value = ft_strjoinfree(*value, to_quot->str_unquoted, 1);
		to_quot = to_quot->next;
	}
}
