/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/18 07:00:56 by mjose            ###   ########.fr       */
=======
/*   Updated: 2019/02/25 05:32:26 by mjose            ###   ########.fr       */
>>>>>>> mjose.merge
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
<<<<<<< HEAD
	while (expand)
	{
		transform_if_tilde(&first_letter, str);
=======
	transform_if_tilde(&first_letter, str);
	while (expand->ltr && expand->ltr != '~')
	{
>>>>>>> mjose.merge
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
<<<<<<< HEAD
//	expand = first_letter;
=======
>>>>>>> mjose.merge
	delete_list_expand(&first_letter);
}
