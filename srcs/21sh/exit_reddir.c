/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_reddir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:28:50 by mjose             #+#    #+#             */
/*   Updated: 2019/04/13 07:29:49 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			exit_reddir(void)
{
	if (g_tracking.builtin == 1 || !g_tracking.temp_command)
	{
		g_tracking.builtin = 0;
		return (-1);
	}
	else
		ft_exit2(EXIT_SUCCESS);
	return (0);
}
