/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 05:42:59 by mjose             #+#    #+#             */
/*   Updated: 2019/03/04 21:26:38 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

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
	if (arg[i] && arg[i] != '$')
		scan_argument(arg + i, info_arg->next, 0);
	else if (arg[i])
		scan_argument(arg + i, info_arg->next, 1);
}

void	scan_argument(char *arg, t_scan *info_arg, int simple)
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
	else if (arg[i] && arg[i] != '}' && !simple)
		while (arg[i] && arg[i] != '}')
		{
			run_arg[i] = arg[i];
			i++;
		}
	else if (arg[i] && arg[i + 1] && arg[i + 1] != '$' && simple)
		while (arg[i] && arg[i + 1] && arg[i + 1] != '$')
		{
			run_arg[i] = arg[i];
			i++;
		}
	if (arg[i] && arg[i + 1] && arg[i + 1] == '$')
	{
		run_arg[i] = arg[i];
		i++;
	}
	else if (simple && arg[i])
	{
		run_arg[i] = arg[i];
		i++;
	}
	split_arg(arg, i, run_arg, info_arg);
	info_arg = first;
}

void	scan_simple_arg_transformer(char **arg)
{
	t_expand	*expand;
	t_scan		*scan;
	t_scan		*first_scan;
	char		*new_arg;

	scan = NULL;
	scan = new_scan();
	first_scan = scan;
	scan_argument(*arg, scan, 1);
	new_arg = NULL;
	while (scan && scan->sstrsing)
	{
		if (!new_arg)
			new_arg = ft_strnew(1);
		if (scan->sstrsing[0] == '$')
		{
			new_arg = ft_strjoinfree(new_arg, get_env_string(scan->sstrsing + 1), 3);
			if (!new_arg)
				new_arg = ft_strjoinfree(new_arg, get_parm_string(scan->sstrsing + 1), 3);
		}
		else
			new_arg = ft_strjoinfree(new_arg, scan->sstrsing, 1);
		if (!new_arg)
		{
			new_arg = ft_strnew(1);
			new_arg = ft_strjoinfree(new_arg, scan->sstrsing, 1);
		}
		scan = scan->next;
	}
	scan = first_scan;
	ft_strdel(arg);
	*arg = new_arg;
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
