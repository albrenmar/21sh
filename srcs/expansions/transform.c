/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
/*   Updated: 2019/02/16 03:11:55 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	transform_if_tilde(t_expand **expand, char **str)
{
	t_expand	**first_letter;
	t_expand	*letter;

	first_letter = expand;
	letter = *expand;
	if (letter->ltr == '~' && !letter->next && !letter->prev)
	{
		expand_tilde_only(str);
		letter = *first_letter;
	}
	else if (letter->ltr == '~' && letter->next && !letter->prev)
	{
		if (letter->next->ltr == '/')
			expand_tilde_path(str, first_letter);
		else if (letter->next->ltr && letter->next->ltr != '-'
				&& letter->next->ltr != '+')
			expand_tilde_user(str, first_letter);
		else if (letter->next->ltr && (letter->next->ltr == '-'
				|| letter->next->ltr == '+'))
			expand_tilde_pwd(str, first_letter);
	}
}

void	transform(t_expand *expand, char **str)
{
	t_expand	*first_letter;
	char		*tmp;

	first_letter = expand;
	tmp = *str;
	while (expand)
	{
		transform_if_tilde(&first_letter, str);
		if (expand->ltr == '$' && expand->next && expand->next->ltr == '{'
				&& !expand->prev && tmp[ft_strlen(tmp) - 1] == '}')
		{
			first_letter = expand_keys(expand, str);
			expand = first_letter;
		}
		if (expand->next)
			expand = expand->next;
		else
			break ;
	}
	expand = first_letter;
}
