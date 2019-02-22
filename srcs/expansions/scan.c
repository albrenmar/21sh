/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 05:42:59 by mjose             #+#    #+#             */
/*   Updated: 2019/02/22 09:05:46 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	split_arg(char *arg, int i, char *run_arg, t_scan *info_arg)
{
	if (run_arg[0])
	{
		if (arg[i] == '}' || (arg[0] == '~' && arg[i]))
		{
			run_arg[i] = arg[i];
			i++;
		}
		info_arg->sstrsing = ft_strdup(run_arg);
	}
	free(run_arg);
	info_arg->next = new_scan();
	if (arg[i])
		scan_argument(arg + i, info_arg->next);
}

void	scan_argument(char *arg, t_scan *info_arg)
{
	char	*run_arg;
	int		i;
	int		error;
	t_scan	*first;

	run_arg = ft_strnew(ft_strlen(arg));
	i = 0;
	error = 0;
	first = info_arg;
	if (arg[i] && arg[i] != '$' && arg[i + 1] && arg[i + 1] != '{')
		while (arg[i] && arg[i] != '$' && arg[i + 1] && arg[i + 1] != '{')
		{
			if (run_arg[i] == '$')
				info_arg->error = i;
			run_arg[i] = arg[i];
			i++;
		}
	else if (arg[i] && arg[i] != '}')
		while (arg[i] && arg[i] != '}')
		{
			run_arg[i] = arg[i];
			i++;
		}
	split_arg(arg, i, run_arg, info_arg);
	info_arg = first;
}

t_scan	*new_scan(void)
{
	t_scan	*scan;

	scan = (t_scan *)malloc(sizeof(t_scan));
	scan->sstrsing = NULL;
	scan->error = -1;
	scan->next = NULL;
	return (scan);
}
