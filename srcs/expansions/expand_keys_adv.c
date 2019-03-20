/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:46:36 by mjose             #+#    #+#             */
/*   Updated: 2019/03/20 00:59:11 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	exp_key_altern(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	ft_strdel(str);
	*str = ft_strdup(to_analy.varvalue);
}

void	exp_key_double_hash(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	char		*run_varvalue;
	char		*run_wildcard;

	init_analyzer(&to_analy, str, expand);
	run_varvalue = to_analy.varvalue;
	run_wildcard = to_analy.wildcard;
	if (to_analy.start_astrsk)
		run_wildcard++;
	if (to_analy.varvalue && !to_analy.asterisk)
		asign_vrvlufnd(&to_analy, &run_varvalue, &run_wildcard, str);
	else if (to_analy.varvalue && to_analy.start_astrsk && !to_analy.end_astrsk)
		asgnvrvluastrk(&to_analy, &run_varvalue, &run_wildcard, str);
	else if (to_analy.varvalue && to_analy.end_astrsk && !to_analy.start_astrsk)
	{
		run_wildcard[to_analy.wlcd_len] = '\0';
		ft_strdel(str);
		if (ft_strnstr(run_varvalue, run_wildcard, to_analy.vvlu_len))
			*str = ft_strdup("");
		else
			*str = ft_strdup(to_analy.varvalue);
	}
	else
		rmv_str(str);
}

void	exp_key_double_percent(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	char		*run_varvalue;
	char		*run_wildcard;
	int			i;

	i = 0;
	init_analyzer(&to_analy, str, expand);
	run_varvalue = to_analy.varvalue;
	run_wildcard = to_analy.wildcard;
	if (to_analy.start_astrsk)
		run_wildcard++;
	if (to_analy.start_astrsk)
		run_wildcard++;
	if (to_analy.varvalue && !to_analy.asterisk)
	{
		run_varvalue = ft_strrev(to_analy.varvalue, 0);
		run_wildcard = ft_strrev(to_analy.wildcard, 0);
		ft_strdel(str);
		if (ft_strnstr(run_varvalue, run_wildcard, to_analy.wlcd_len))
		{
			*str = ft_strdup(run_varvalue + to_analy.wlcd_len);
			*str = ft_strrev(*str, 1);
		}
		else
			*str = ft_strdup(to_analy.varvalue);
	}
	else if (to_analy.varvalue && to_analy.start_astrsk && !to_analy.end_astrsk)
	{
		run_varvalue = ft_strrev(to_analy.varvalue, 0);
		run_wildcard = ft_strrev(to_analy.wildcard + 1, 0);
		ft_strdel(str);
		if (ft_strnstr(run_varvalue, run_wildcard, to_analy.wlcd_len))
			*str = ft_strdup("");
		else
			*str = ft_strdup(to_analy.varvalue);
	}
	else if (to_analy.varvalue && to_analy.end_astrsk && !to_analy.start_astrsk)
	{
		run_wildcard[to_analy.wlcd_len] = '\0';
		while (*run_varvalue && !ft_strnstr(run_varvalue, run_wildcard, to_analy.wlcd_len))
		{
			run_varvalue++;
			i++;
		}
		run_varvalue = ft_strrev(to_analy.varvalue, 0);
		ft_strdel(str);
		*str = ft_strdup(ft_strrev(run_varvalue + (to_analy.vvlu_len - i), 0));
	}
	else
		rmv_str(str);
/*	char	*varname;
	char	*value_var;
	char	*to_srch;
	char	*found;

	varname = NULL;
	to_srch = NULL;
	varname = get_varname(expand);
	value_var = get_env_string(varname);
	to_srch = get_value_asterisk(expand);
	if (value_var && (found = ft_strstr(value_var, to_srch)))
		select_last_not_found(str, value_var, to_srch, found);
	else if (value_var)
	{
		ft_strdel(str);
		*str = value_var;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strnew(0);
	}*/
}
