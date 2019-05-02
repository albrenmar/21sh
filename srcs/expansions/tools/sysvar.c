/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:40:01 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 02:22:50 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		assign_to_curpid(char **str)
{
	ft_strdel(str);
	*str = ft_itoa(getpid());
	return (1);
}

int		assign_to_lastreturn(char **str)
{
	ft_strdel(str);
	*str = ft_itoa(g_tracking.expandreturn);
	return (1);
}

int		assign_to_shell_name(char **str)
{
	ft_strdel(str);
	*str = ft_strdup(SHELL_NAME);
	return (1);
}

int		assign_to_lastbackground(char **str)
{
	ft_strdel(str);
	*str = ft_itoa(g_tracking.lastbackground);
	return (1);
}

int		assign_to_lastargument(char **str)
{
	ft_strdel(str);
	*str = ft_strdup(g_tracking.last_arg);
	return (1);
}
