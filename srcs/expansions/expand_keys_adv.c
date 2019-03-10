/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_adv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:46:36 by mjose             #+#    #+#             */
/*   Updated: 2019/03/10 15:39:23 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	exp_key_double_hash(char **str, t_expand *expand)
{
	char	*varname;
	char	*value_var;
	char	*to_srch;
	char	*tmp2;
	char	*tmp3;

	varname = NULL;
	to_srch = NULL;
	varname = get_varname(expand);
	value_var = get_env_string(varname);
	to_srch = get_asterisk_value(expand);
	tmp3 = to_srch;
	tmp2 = value_var;
	if (value_var)
	{
		while (ft_strstr(tmp2, to_srch))
			tmp2++;
		if (tmp2)
			while (*tmp3 != '\0' && *(tmp3 + 1) == *tmp2)
			{
				tmp2++;
				tmp3++;
			}
		ft_strdel(str);
		*str = ft_strdup(tmp2);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strdup("");
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
