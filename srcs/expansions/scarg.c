/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scarg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 01:03:07 by mjose             #+#    #+#             */
/*   Updated: 2019/03/23 05:41:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void		expan_arg(t_scan_arg *scarg)
{
	scarg->expand = new_expand(ft_strlen(scarg->scan->sstring));
	create_list_expand(scarg->expand, scarg->scan->sstring);
	if ((scarg->scan->sstring[0] != '~' && !scarg->checker->type)
			|| scarg->scan->sstring[0] == '$')
		transform(scarg->expand, &scarg->scan->sstring);
	else if (scarg->scan->sstring[0] == '~')
		transform_if_tilde(&scarg->expand, &scarg->scan->sstring);
	if (!scarg->new_arg)
		scarg->new_arg = ft_strnew(1);
	scarg->new_arg = ft_strjoinfree(scarg->new_arg, scarg->scan->sstring, 1);
	scarg->scan = scarg->scan->next;
}

void		fill_scarg(t_scan_arg *scarg)
{
	scarg->scan = new_scan();
	scarg->first_scan = scarg->scan;
	scan_argument(scarg->checker->str_unquoted, scarg->scan);
	scarg->new_arg = NULL;
	while (scarg->scan && scarg->scan->sstring)
		expan_arg(scarg);
	while (scarg->first_scan->sstring)
	{
		ft_strdel(&scarg->first_scan->sstring);
		ft_memdel((void **)scarg->first_scan);
		scarg->first_scan = scarg->first_scan->next;
	}
	if (scarg->first_scan)
		ft_memdel((void **)scarg->first_scan);
	scarg->first_scan = NULL;
	if (scarg->new_arg)
	{
		ft_strdel(&scarg->checker->str_unquoted);
		scarg->checker->str_unquoted = scarg->new_arg;
	}
}
