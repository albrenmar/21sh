/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 06:17:07 by mjose             #+#    #+#             */
/*   Updated: 2019/04/08 10:53:02 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh21.h"

void	print_exp_error_dpoints(char *varname, char *value, int sign)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ${", 2);
	ft_putstr_fd(varname, 2);
	ft_putchar_fd(':', 2);
	ft_putchar_fd(sign, 2);
	ft_putstr_fd(value, 2);
	ft_putendl_fd("}: bad substitution", 2);
	g_tracking.mysh->err_expend = 1;
}

void	print_exp_error_eq(char *varname, char *value)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(value, 2);
	g_tracking.mysh->err_expend = 1;
}

void	print_exp_error(char *to_error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ${", 2);
	if (to_error)
		ft_putstr_fd(to_error, 2);
	ft_putendl_fd("}: bad substitution", 2);
	g_tracking.mysh->err_expend = 1;
}

void	print_exp_str_error(char *strerror)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (strerror)
		ft_putstr_fd(strerror, 2);
	ft_putendl_fd(": bad substitution", 2);
	g_tracking.mysh->err_expend = 1;
}
