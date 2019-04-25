/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:23:11 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/24 12:23:59 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		digit_or_str(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		if (ft_isdigit(str[i]) == 1)
			return (0);
		if (str[i] == '+' || str[i] == '-')
		{
			i++;
			if (ft_isdigit(str[i]) == 1)
				return (0);
		}
	}
	return (1);
}

int		fc_get_index(char *str)
{
	t_list		*history;
	char		*buf;
	int			i;

	if (!g_tracking.mysh->hist)
		return (fc_error(4, str));
	if (!str)
		return (-42);
	history = ft_lstgetlast(g_tracking.mysh->hist->firstelement);
	if (!history)
		return (fc_error(4, str));
	i = ft_strlen(str);
	while (history)
	{
		buf = history->content;
		if (ft_strncmp(str, buf, i) == 0)
			return (history->index);
		history = history->prev;
	}
	return (fc_error(4, str));
}

void	char_to_index(t_fcparse *opt)
{
	int		tmp;

	tmp = 0;
	if (digit_or_str(opt->first) == 0)
		opt->low = ft_atoi(opt->first);
	else
		opt->low = fc_get_index(opt->first);
	if (digit_or_str(opt->last) == 0)
		opt->max = ft_atoi(opt->last);
	else
		opt->max = fc_get_index(opt->last);
	if (opt->low > opt->max)
	{
		tmp = opt->low;
		opt->low = opt->max;
		opt->max = tmp;
		tmp = opt->r;
		if (tmp == 1)
			opt->r = 0;
		if (tmp == 0)
			opt->r = 1;
	}
}