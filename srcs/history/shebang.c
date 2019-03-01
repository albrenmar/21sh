/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/01 19:09:37 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		shebang_parse_switch(t_hist *hist, char **arg_tab)
{
	int 	i;
	char	*tmp_str;

	i = 0;
	while (arg_tab[i])
	{
		if (tmp_str = ft_strdup(ft_strchr(arg_tab[i], '!')))
		{
			
		}
	}
}