/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 00:47:03 by mjose             #+#    #+#             */
/*   Updated: 2019/02/05 01:30:54 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	exp_key_start_hash(char **str, t_expand *expand)
{
	char	*varname;
	char	*value;

	varname = get_varname(expand);
	value = get_env_string(varname);
	ft_strdel(str);
	*str = ft_itoa(ft_strlen(value));
	ft_strdel(&varname);
	ft_strdel(&value);
}

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
	ft_strdel(str);
	if (value1)
		*str = value1;
	else
	{
		ft_putstr_fd(str1, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value2, 2);
		ft_strdel(&value1);
		ft_strdel(&str1);
		ft_strdel(&str2);
		str = NULL;
		ft_putendl("Exit temporaire, mauvais parametre");
		exit(1);
	}
}

void	exp_key_equal(char **str, t_expand *expand)
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
	if (value1)
		*str = value1;
	else
	{
		ft_strdel(&value1);
		*str = value2;
		replace_env_str(str1, value2);
		ft_strdel(&str1);
	}
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

char	check_sign(t_expand *expand)
{
	t_expand	*to_run;
	int			ctrl;
	char		sign;

	to_run = expand;
	sign = '\0';
	while (to_run)
	{
		if (to_run->ltr == ':')
		{
			if (to_run->next->ltr == '-')
				sign = '-';
			else if (to_run->next->ltr == '=')
				sign = '=';
			else if (to_run->next->ltr == '?')
				sign = '?';
			else if (to_run->next->ltr == '+')
				sign = '+';
		}
		else if (to_run->ltr == '#' && to_run->prev && to_run->prev->ltr == '{')
			sign = '@';
		else if (to_run->ltr == '#' && to_run->next && to_run->next->ltr != '}'
				&& to_run->prev && to_run->prev->ltr != '{'
				&& to_run->prev->ltr != '#')
			sign = '#';
		else if (to_run->ltr == '#' && to_run->next && to_run->next->ltr == '#'
				&& to_run->next->next && to_run->next->next->ltr != '}'
				&& to_run->prev && to_run->prev->ltr != '{'
				&& to_run->prev->ltr != '#')
			sign = '3';
		else if (to_run->ltr == '%' && to_run->next && to_run->next->ltr != '}'
				&& to_run->prev && to_run->prev->ltr != '{'
				&& to_run->prev->ltr != '%')
			sign = '%';
		else if (to_run->ltr == '%' && to_run->next && to_run->next->ltr == '%'
				&& to_run->next->next && to_run->next->next->ltr != '}'
				&& to_run->prev && to_run->prev->ltr != '{'
				&& to_run->prev->ltr != '%')
			sign = '5';
		to_run = to_run->next;
	}
	return (sign);
}

t_expand	*expand_keys(t_expand *expand, char **str)
{
	char		sign;

	sign = check_sign(expand);
	if (sign == '-')
		exp_key_less(str, expand);
	else if (sign == '=')
		exp_key_equal(str, expand);
	else if (sign == '?')
		exp_key_inter(str, expand);
	else if (sign == '+')
		exp_key_plus(str, expand);
	else if (sign == '@')
		exp_key_start_hash(str, expand);
	update_list_expand(&expand, str);
	return (expand);
}
