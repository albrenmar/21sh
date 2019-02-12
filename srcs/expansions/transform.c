/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
/*   Updated: 2019/02/12 02:24:13 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	transform_if_tilde(t_expand *expand, char **str)
{
	t_expand	*first_letter;

	first_letter = expand;
	if (expand->ltr == '~' && !expand->next && !expand->prev)
		expand_tilde_only(str);
	else if (expand->ltr == '~' && expand->next && !expand->prev)
	{
		if (expand->next->ltr == '/')
			expand_tilde_path(str, &first_letter);
		else if (expand->next->ltr && expand->next->ltr != '-'
				&& expand->next->ltr != '+')
			expand_tilde_user(str, &first_letter);
		else if (expand->next->ltr && (expand->next->ltr == '-'
				|| expand->next->ltr == '+'))
			expand_tilde_pwd(str, &first_letter);
		expand = first_letter;
	}
}

void	transform(t_expand *expand, char **str)
{
	t_expand	*first_letter;

	first_letter = expand;
	while (expand)
	{
		transform_if_tilde(expand, str);
		if (expand->ltr == '$' && expand->next && expand->next->ltr == '{'
				&& !expand->prev && *str[ft_strlen(*str) == '}'])
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
