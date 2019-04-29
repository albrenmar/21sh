/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 09:35:06 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		reset_tmpenv(void)
{
	// t_tmpenv	*hold;
	// t_tmpenv	*tmp;

	// tmp = g_tracking.mysh->tmpenv;
	// if (tmp)
	// {
	// 	while (tmp->next)
	// 	{
	// 		hold = tmp->next;
	// 		ft_strdel(&tmp->value);
	// 		ft_strdel(&tmp->key);
	// 		ft_free(tmp);
	// 		tmp = hold;
	// 	}
	// 	ft_strdel(&tmp->value);
	// 	ft_strdel(&tmp->key);
	// 	ft_free(tmp);
	// }
	// g_tracking.mysh->tmpenv = NULL;
}
