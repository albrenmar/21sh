/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
/*   Updated: 2019/01/30 23:46:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	transform(t_expand *expand, char **str)
{
	if (expand->ltr == '~' && !expand->next)
		expand_tilde_only(str);
	else if (expand->ltr == '~' && expand->next->ltr == '/')
		expand_tilde_path(str);
}
