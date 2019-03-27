/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:10:51 by mjose             #+#    #+#             */
/*   Updated: 2019/03/27 04:25:27 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char		*get_value_asterisk(t_expand *expand)
{
	int			i;
	char		*value;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next;
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
	return (value_asterisk(value, to_run->next->next));
}

char		*get_asterisk_value(t_expand *expand)
{
	int			i;
	char		*val;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next;
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
	while (start && start->ltr != '*')
	{
		start = start->next;
		i++;
	}
	val = ft_strnew(i);
	return (value(val, to_run->next->next));
}

t_expand	*run_to_value(t_expand *ato_run)
{
	t_expand	*to_run;

	to_run = ato_run;
	if (to_run->ltr == '#' || to_run->ltr == '%' || to_run->ltr == '/')
	{
		if (to_run->next && to_run->prev)
			if (to_run->next->ltr == '#' || to_run->next->ltr == '%')
				to_run = to_run->next;
		to_run = to_run->prev;
	}
	return (to_run);
}

int			val_len(t_expand *start)
{
	int i;

	i = 0;
	while (start && start->ltr != '}')
	{
		if (start)
		{
			start = start->next;
			i++;
		}
		else
			break ;
	}
	return (i);
}

char		*get_value(t_expand *expand, int i)
{
	char		*val;
	t_expand	*start;
	t_expand	*to_run;

	to_run = expand->next;
	while (to_run && to_run->ltr != ':' && to_run->ltr != '#'
			&& to_run->ltr != '%' && to_run->ltr != '/')
		to_run = to_run->next;
	if (!to_run && to_run->prev->ltr == '$')
		return (NULL);
	to_run = run_to_value(to_run);
	if (!to_run->next)
		return (NULL);
	if (!to_run->next->next)
		return (ft_strdup(""));
	start = to_run->next->next;
	i = val_len(start);
	if (!i)
		return (NULL);
	val = ft_strnew(i + 1);
	return (value(val, to_run->next->next));
}
