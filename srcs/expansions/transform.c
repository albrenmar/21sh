/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
/*   Updated: 2019/02/01 05:52:06 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	transform(t_expand *expand, char **str)
{
	t_expand	*first_letter;

	first_letter = expand;
	while (expand)
	{
		if (expand->ltr == '~' && !expand->next && !expand->prev)
			expand_tilde_only(str);
		else if (expand->ltr == '~' && expand->next)
		{
			if (expand->next->ltr == '/' && !expand->prev)
				expand_tilde_path(str, &first_letter);
			else if (expand->next->ltr == '/' && expand->prev->ltr == '/')
				expand_path_tilde_path(str, &first_letter, expand->idx);
			expand = first_letter;
		}
		if (expand->next)
			expand = expand->next;
		else
			break ;
	}
	expand = first_letter;
}
