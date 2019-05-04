/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:41:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:00:34 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	begin_paste(void)
{
	char	*tmp;

	if (!g_tracking.cpaste || !g_tracking.cpaste->line)
		return ;
	tmp = ft_strdup(g_tracking.cpaste->line);
	if (g_tracking.cpaste->line)
		add_to_str(tmp);
	else
		ft_strdel(&tmp);
}
