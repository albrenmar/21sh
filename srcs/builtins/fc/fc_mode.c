/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 22:12:59 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/27 22:17:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		editor_mode(t_fcparse *opt)
{
	if (opt->low && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = opt->low;
	if (opt->low == -42)
		opt->low = opt->max;
	create_fc_file(opt);
	return (0);
}

int		no_edit_mode(t_fcparse *opt)
{
	if (opt->low == -4 && opt->max == -42)
		opt->max = -1;
	if (opt->low == -42 && opt->max == -42)
	{
		opt->low = -1;
		opt->max = -1;
	}
	create_fc_oldnew(opt);
	return (0);
}

int		list_mode(t_fcparse *opt)
{
	if (opt->low && opt->max == -42)
	{
		opt->low = -15;
		opt->max = -1;
	}
	if (opt->max == -42)
		opt->max = -1;
	print_fc(opt);
	return (0);
}

int		fc_mode(t_fcparse *opt)
{
	if ((opt->e == 1 && opt->s == 1) || (opt->e == 1 && opt->l == 1))
		return (fc_error(3, NULL));
	if ((opt->l == 1 && opt->s == 1) || (opt->l == 1 && opt->e == 1))
		return (fc_error(3, NULL));
	if ((opt->s == 1 && opt->n == 1) || (opt->e == 1 && opt->n == 1))
		return (fc_error(3, NULL));
	if (opt->e == 1)
		return (editor_mode(opt));
	if (opt->s == 1)
		return (no_edit_mode(opt));
	if (opt->l == 1)
		return (list_mode(opt));
	return (editor_mode(opt));
}
