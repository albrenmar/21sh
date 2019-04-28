/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 06:17:07 by mjose             #+#    #+#             */
/*   Updated: 2019/04/28 22:32:45 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	print_exp_error_dpoints(char *varname, char *value, int sign,
			char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ${", 2);
		ft_putstr_fd(varname, 2);
		ft_putchar_fd(':', 2);
		ft_putchar_fd(sign, 2);
		ft_putstr_fd(value, 2);
		ft_putendl_fd("}: bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinchar(*str, ':', 1);
		*str = ft_strjoinchar(*str, sign, 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_error_eq(char *varname, char *value, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value, 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinfree(*str, ":=", 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_error_inter(char *varname, char *value, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value, 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinfree(*str, ":?", 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_error(char *to_error, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ${", 2);
		if (to_error)
			ft_putstr_fd(to_error, 2);
		ft_putendl_fd("}: bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", to_error, 0);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_token_error(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	char		*run_str;
	t_expand	*run_expand;

	run_str = ft_strdup(*str + 2);
	run_str[ft_strlen(run_str) - 1] = '\0';
	run_expand = expand->next;
	init_analyzer(&to_analy, &run_str, run_expand);
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		if (to_analy.varvalue)
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(ft_strjoinfree(": ", to_analy.varname, 0), 2);
			ft_putstr_fd(ft_strjoinfree(": ", ft_strchr(run_str, ':') + 1, 0), 2);
			ft_putstr_fd(": syntax error: operand expected (error token is \"", 2);
			ft_putstr_fd(ft_strchr(run_str, ':') + 1, 2);
			ft_putendl_fd("\")", 2);
		}
//		if (to_error)
//			ft_putstr_fd(to_error, 2);
//		ft_putendl_fd("}: bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
		g_tracking.mysh->err_expend = 1;
	ft_strdel(&run_str);
}

void	print_exp_str_error(char *strerror, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		if (strerror)
			ft_putstr_fd(strerror, 2);
		ft_putendl_fd(": bad substitution", 2);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", strerror, 0);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_scan_error(char *strerror)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		if (strerror)
			ft_putstr_fd(strerror, 2);
		ft_putendl_fd(": bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
		g_tracking.mysh->err_expend = 1;
}

