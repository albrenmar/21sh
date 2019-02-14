/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:10:51 by mjose             #+#    #+#             */
/*   Updated: 2019/02/14 06:14:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*get_value_asterisk(t_expand *expand)
{
	int			i;
	char		*value;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next->next;
	while (to_run->ltr != ':' && to_run->ltr != '%')
		to_run = to_run->next;
	if (to_run->ltr == '%')
	{
		if (to_run->next->ltr == '%')
			to_run = to_run->next;
		to_run = to_run->prev;
	}
	start = to_run->next->next;
	while (start->ltr != '*')
	{
		start = start->next;
		i++;
	}
	value = ft_strnew(i);
	start = to_run->next->next;
	i = 0;
	while (start->ltr != '*')
	{
		value[i++] = start->ltr;
		start = start->next;
	}
	return (value);
}

char	*get_asterisk_value(t_expand *expand)
{
	int			i;
	char		*value;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next->next;
	while (to_run->ltr != ':' && to_run->ltr != '#')
		to_run = to_run->next;
	if (to_run->ltr == '#')
	{
		if (to_run->next->ltr == '#')
			to_run = to_run->next;
		if (to_run->next->ltr == '*')
			to_run = to_run->next;
		to_run = to_run->prev;
	}
	start = to_run->next->next;
	while (start->ltr != '}')
	{
		start = start->next;
		i++;
	}
	value = ft_strnew(i);
	start = to_run->next->next;
	i = 0;
	while (start->ltr != '}')
	{
		value[i++] = start->ltr;
		start = start->next;
	}
	return (value);
}

char	*get_value(t_expand *expand)
{
	int			i;
	char		*value;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next->next;
	while (to_run->ltr != ':' && to_run->ltr != '#' && to_run->ltr != '%')
		to_run = to_run->next;
	if (to_run->ltr == '#' || to_run->ltr == '%')
	{
		if (to_run->next->ltr == '#' || to_run->next->ltr == '%')
			to_run = to_run->next;
		to_run = to_run->prev;
	}
	start = to_run->next->next;
	while (start->ltr != '}')
	{
		start = start->next;
		i++;
	}
	value = ft_strnew(i);
	start = to_run->next->next;
	i = 0;
	while (start->ltr != '}')
	{
		value[i++] = start->ltr;
		start = start->next;
	}
	return (value);
}

char	*get_varname(t_expand *expand)
{
	int			i;
	char		*varname;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next->next;
	if (to_run->ltr == '#' && to_run->ltr == '%')
		to_run = to_run->next;
	while (to_run->ltr != ':' && to_run->ltr != '}'
			&& to_run->ltr != '#' && to_run->ltr != '%')
	{
		to_run = to_run->next;
		i++;
	}
	varname = ft_strnew(i);
	to_run = expand->next->next;
	i = 0;
	if (to_run->ltr == '#' && to_run->ltr != '%')
		to_run = to_run->next;
	while (to_run->ltr != ':' && to_run->ltr != '}'
			&& to_run->ltr != '#' && to_run->ltr != '%')
	{
		varname[i++] = to_run->ltr;
		to_run = to_run->next;
	}
	return (varname);
}
