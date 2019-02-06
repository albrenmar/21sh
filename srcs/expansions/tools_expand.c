/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 01:23:51 by mjose             #+#    #+#             */
/*   Updated: 2019/02/06 04:17:16 by mjose            ###   ########.fr       */
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
	while (to_run->ltr != ':' && to_run->ltr != '$')
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

void	delete_letter_expand(t_expand **letter)
{
	t_expand	*prev;
	t_expand	*next;

	prev = (*letter)->prev;
	next = (*letter)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(*letter);
	if (next)
		*letter = next;
	else
		*letter = NULL;
}

void	delete_list_expand(t_expand **letter)
{
	t_expand	*next;

	next = NULL;
	while (*letter && (*letter)->next)
	{
		if ((*letter)->next)
			next = (*letter)->next;
		delete_letter_expand(letter);
		if (next)
			*letter = next;
		else
			*letter = NULL;
	}
	*letter = NULL;
}

void	update_list_expand(t_expand **letter, char **str)
{
	t_expand	*new_letter;

	delete_list_expand(letter);
	*letter = NULL;
	new_letter = new_expand(ft_strlen(*str));
	*letter = new_letter;
	create_list_expand(*letter, *str);
}
