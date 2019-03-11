/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:01:55 by mjose             #+#    #+#             */
/*   Updated: 2019/03/11 16:27:19 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	init_analyzer(t_analyzer *to_analy, char **str, t_expand *expand)
{
	to_analy->orig_str = *str;
	to_analy->orig_len = ft_strlen(to_analy->orig_str);
	to_analy->varname = get_varname(expand);
	to_analy->vnme_len = ft_strlen(to_analy->varname);
	to_analy->varvalue = get_env_string(to_analy->varname);
	to_analy->vvlu_len = ft_strlen(to_analy->varvalue);
	to_analy->wildcard = get_value(expand);
	to_analy->wlcd_len = ft_strlen(to_analy->wildcard);
	to_analy->start_astrsk = 0;
	to_analy->end_astrsk = 0;
	if (to_analy->wildcard && (to_analy->wildcard[to_analy->wlcd_len - 1] == '*'
			|| to_analy->wildcard[0] == '*'))
	{
		to_analy->asterisk = 1;
		to_analy->wlcd_len--;
		if (to_analy->wildcard[0] == '*')
			to_analy->start_astrsk = 1;
		if (to_analy->wildcard[to_analy->wlcd_len] == '*')
			to_analy->end_astrsk = 1;
	}
	else
		to_analy->asterisk = 0;
}
