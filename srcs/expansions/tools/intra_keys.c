/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intra_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 00:08:56 by mjose             #+#    #+#             */
/*   Updated: 2019/04/26 00:39:01 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

t_unquoter	*re_create_intra_keys(t_unquoter *to_unquot, char **tmp)
{
	t_unquoter	*first;
	char		*run_tmp;

	run_tmp = ft_strnew(1);
	first = to_unquot;
	while (to_unquot)
	{
		run_tmp = ft_strjoinfree(run_tmp, to_unquot->str_unquoted, 1);
		to_unquot = to_unquot->next;
	}
	to_unquot = first;
	if (run_tmp[0] == '$' && run_tmp[1]
		== '{' && run_tmp[ft_strlen(run_tmp) - 1] == '}')
	{
		clean_unquoter(first);
		to_unquot = new_unquoted_value();
		to_unquot->str_unquoted = ft_strdup(run_tmp);
	}
	*tmp = run_tmp;
	return (to_unquot);
}
