/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 02:50:02 by mjose             #+#    #+#             */
/*   Updated: 2019/01/29 03:09:43 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	tilde_transformer(t_expand *new_letter, t_env *env, char *line)
{
	int			i;
	t_expand	*frst_letter;

	i = 0;
	frst_letter = new_letter;
	while (line[i])
	{
		new_letter->ltr = line[i];
		if (line[i + 1] && !ft_iswhitespace(line[i]))
		{
			new_letter->next = new_expand();
		}
	}
}
