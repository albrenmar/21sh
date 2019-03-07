/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_dblpnt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:41:37 by mjose             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/04 11:29:23 by mjose            ###   ########.fr       */
=======
/*   Updated: 2019/02/22 07:34:29 by mjose            ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	exp_key_plus(char **str, t_expand *expand)
{
	char	*str1;
	char	*str2;
	char	*value1;
	char	*value2;

	str1 = NULL;
	str2 = NULL;
	str1 = get_varname(expand);
	str2 = get_value(expand);
	value1 = get_env_string(str1);
	if (!value1)
		value1 = get_parm_string(str1);
	value2 = str2;
	ft_strdel(str);
	ft_strdel(&str1);
	if (value1)
	{
		*str = value2;
		ft_strdel(&value1);
	}
	else
	{
		ft_strdel(&value2);
		*str = NULL;
	}
}

void	exp_key_inter(char **str, t_expand *expand)
{
	char	*str1;
	char	*str2;
	char	*value1;
	char	*value2;

	str1 = NULL;
	str2 = NULL;
	str1 = get_varname(expand);
	str2 = get_value(expand);
	value1 = get_env_string(str1);
	if (!value1)
		value1 = get_parm_string(str1);
	value2 = str2;
<<<<<<< HEAD
//	ft_strdel(str);
	free(*str);
=======
	ft_strdel(str);
>>>>>>> alsomvil
	if (value1)
		*str = value1;
	else
	{
<<<<<<< HEAD
		ft_strdel(&value1);
		print_exp_error_eq(str1, str2);
		ft_strdel(&str1);
		ft_strdel(&str2);
		*str = ft_strdup("");
		g_tracking.mysh->expand_error = 1;
=======
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value2, 2);
		ft_strdel(&value1);
		ft_strdel(&str1);
		ft_strdel(&str2);
		str = NULL;
		ft_putendl("Exit temporaire, mauvais parametre");
		exit(1);
>>>>>>> alsomvil
	}
}

void	exp_key_equal(char **str, t_expand *expand)
{
	char	*str1;
	char	*str2;
	char	*value1;
	char	*value2;
	int		env_or_set;

	str1 = NULL;
	str2 = NULL;
	value1 = NULL;
	str1 = get_varname(expand);
	str2 = get_value(expand);
	value1 = get_env_string(str1);
	if (!value1)
		value1 = get_parm_string(str1);
	value2 = str2;
	ft_strdel(str);
	env_or_set = have_envname(str1);
<<<<<<< HEAD
	if (value1 && !ft_strequ(value1, ""))
=======
	if (value1 && ft_strequ(value1, ""))
>>>>>>> alsomvil
		*str = value1;
	else if (env_or_set == 1)
		replace_env_str(str1, value2);
	else if (env_or_set == 2 || !env_or_set)
		replace_env_set_str(str1, value2);
	ft_strdel(&str1);
<<<<<<< HEAD
	if (!*str)
		*str = value2;
=======
	*str = value2;
>>>>>>> alsomvil
}

void	exp_key_less(char **str, t_expand *expand)
{
	char	*str1;
	char	*str2;
	char	*value1;
	char	*value2;

	str1 = NULL;
	str2 = NULL;
	str1 = get_varname(expand);
	str2 = get_value(expand);
	value1 = get_env_string(str1);
	if (!value1)
		value1 = get_parm_string(str1);
	value2 = str2;
	ft_strdel(str);
	ft_strdel(&str1);
	if (value1)
	{
		ft_strdel(&value2);
		*str = value1;
	}
	else
	{
		ft_strdel(&value1);
		*str = value2;
	}
}
