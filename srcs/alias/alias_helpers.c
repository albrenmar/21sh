/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char			*check_if_first_word_helper(char *str, int isa, int save, int j)
{
	t_list		*hold;
	t_keyval	*tmp;

	hold = NULL;
	if (g_tracking.mysh->alias_lst)
		hold = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (hold)
	{
		tmp = hold->content;
		j = 0;
		save = isa;
		while (tmp->key[j] && str[isa] && str[isa] != '\t'
			&& str[isa] != ' ' && str[isa] != '\r' && str[isa] != '\v'
			&& str[isa] != '\n' && str[isa] == tmp->key[j])
		{
			j++;
			isa++;
		}
		if (!(tmp->key[j]) && (!(str[isa])
		|| (str[isa] && (is_spaces(str, isa, 2)))))
			return (swap_alias(str, j, save, tmp));
		hold = hold->next;
	}
	return (str);
}

char			*check_if_first_word_alias(char *str, int i, int isave)
{
	int		count;

	while (is_spaces(str, i, 2))
		i++;
	while (str[i])
	{
		count = 0;
		if (!is_spaces(str, i, 2))
		{
			isave = i;
			count = 1;
		}
		while (str[i] && !is_spaces(str, i, 2))
		{
			if (str[i] == '=')
				count++;
			i++;
		}
		if (count == 1 && !is_spaces(str, isave, 2))
			return (check_if_first_word_helper(str, isave, 0, 0));
		if (str[i])
			i++;
	}
	return (str);
}
