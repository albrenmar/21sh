/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 06:45:56 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

// void			init_tmp_env(char *str, int jsave, int save, int cmdindex)
// {
// 	t_tmpenv	*tmp;

// 	tmp = g_tracking.mysh->tmpenv;
// 	if (g_tracking.mysh->tmpenv == NULL)
// 	{
// 		if (!(g_tracking.mysh->tmpenv = ft_malloc(sizeof(t_tmpenv))))
// 			return ;
// 		tmp = g_tracking.mysh->tmpenv;
// 		tmp->cmdindex = cmdindex;
// 		tmp->key = tmp_env_namemaker(str, jsave);
// 		tmp->value = tmp_env_namemaker(str, save + 1);
// 	}
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		if (!(tmp->next = ft_malloc(sizeof(t_tmpenv))))
// 			return ;
// 		tmp = tmp->next;
// 		tmp->cmdindex = cmdindex;
// 		tmp->key = tmp_env_namemaker(str, jsave);
// 		tmp->value = tmp_env_namemaker(str, save + 1);
// 	}
// 	tmp->next = NULL;
// }
