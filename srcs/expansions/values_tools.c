/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:23:41 by mjose             #+#    #+#             */
/*   Updated: 2019/03/10 16:20:09 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*value_asterisk(char *val, t_expand *start)
{
	int		i;

	i = 0;
	while (start->ltr != '*')
	{
		val[i++] = start->ltr;
		start = start->next;
	}
	return (val);
}

char	*value(char *val, t_expand *start)
{
	int		i;

	i = 0;
	while (start && start->ltr != '*')
	{
		val[i++] = start->ltr;
		start = start->next;
	}
	return (val);
}

char	*varname(char *var, t_expand *to_run)
{
	int		i;

	i = 0;
	if (to_run->ltr == '#' && to_run->ltr != '%')
		to_run = to_run->next;
	while (to_run->ltr != ':' && to_run->ltr != '}'
			&& to_run->ltr != '#' && to_run->ltr != '%')
	{
		var[i++] = to_run->ltr;
		to_run = to_run->next;
	}
	return (var);
}
