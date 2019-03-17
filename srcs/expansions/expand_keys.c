/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 00:47:03 by mjose             #+#    #+#             */
/*   Updated: 2019/03/17 03:09:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void		exp_key_unique_percent(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	if (to_analy.varvalue)
	{
		to_analy.varvalue = ft_strrev(to_analy.varvalue, 1);
		clean_nlzr_wildcard(&to_analy, 1);
	}
	str_uniq_percent_chgr(&to_analy, str);
}

void		exp_key_unique_hash(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	clean_nlzr_wildcard(&to_analy, 0);
	if (to_analy.varvalue && ft_strnstr(to_analy.varvalue, to_analy.wildcard,
			to_analy.wlcd_len))
		skip_found(str, to_analy.varvalue, to_analy.wildcard);
	else if (to_analy.varvalue)
	{
		ft_strdel(str);
		*str = to_analy.varvalue;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strdup("");
	}
}

void		exp_key_start_hash(char **str, t_expand *expand)
{
	char		*varname;
	char		*value;

	varname = get_varname(expand);
	value = get_env_string(varname);
	ft_strdel(str);
	*str = ft_itoa(ft_strlen(value));
	ft_strdel(&varname);
	ft_strdel(&value);
}

char		check_sign(t_expand *expand)
{
	t_expand	*to_run;
	int			ctrl;
	char		sign;

	to_run = expand;
	sign = '\0';
	while (to_run)
	{
		if (!sign)
		{
			sign = is_two_points_sign(to_run);
			if (!sign)
				sign = is_diferent_sign(to_run);
		}
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
	else if (sign == '#')
		exp_key_unique_hash(str, expand);
	else if (sign == '3')
		exp_key_double_hash(str, expand);
	else if (sign == '%')
		exp_key_unique_percent(str, expand);
	else if (sign == '5')
		exp_key_double_percent(str, expand);
	else if (sign == '*')
		exp_key_altern(str, expand);
	update_list_expand(&expand, str);
	return (expand);
}
