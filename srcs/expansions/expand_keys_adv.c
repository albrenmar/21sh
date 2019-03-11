/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:46:36 by mjose             #+#    #+#             */
/*   Updated: 2019/03/11 11:16:55 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	exp_key_double_hash(char **str, t_expand *expand)
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
	if (to_analy.varvalue && !to_analy.asterisk)
	{
		if (ft_strstr(run_varvalue, run_wildcard))
		{
			ft_strdel(str);
			*str = ft_strdup(run_varvalue + to_analy.wlcd_len);
		}
	}
	else if (to_analy.varvalue && to_analy.start_astrsk)
	{
		run_varvalue = ft_strrev(run_varvalue, 0);
		run_wildcard = ft_strrev(run_wildcard, 0);
		if (!ft_strnstr(run_varvalue, run_wildcard, to_analy.wlcd_len))
			while (!ft_strnstr(run_varvalue, run_wildcard, to_analy.wlcd_len))
			{
				run_varvalue++;
				i++;
				if (!run_varvalue || i > to_analy.vvlu_len)
					break ;
			}
		ft_strdel(str);
		if (i > to_analy.vvlu_len)
			*str = ft_strdup(to_analy.varvalue);
		else
			*str = ft_strdup(to_analy.varvalue + (to_analy.vvlu_len - i));
	}
	else if (to_analy.varvalue && to_analy.end_astrsk)
	{
		run_wildcard[to_analy.wlcd_len] = '\0';
		ft_strdel(str);
		if (ft_strstr(run_varvalue, run_wildcard))
			*str = ft_strdup("");
		else
			*str = ft_strdup(to_analy.varvalue);
	}
}

void	exp_key_double_percent(char **str, t_expand *expand)
{
	char	*varname;
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
	}
}
