/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 05:55:45 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 02:00:57 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		heredoc_expander(char **str)
{
	char	*run_str;
	char	*tmp;
	int		count_q;
	int		i;

	g_tracking.mysh->in_here = 1;
	run_str = ft_strdup(*str);
	tmp = *str;
	if ((i = check_basic_quotes(*str)) > 0 && i == 3)
	{
		i = 0;
		count_q = 0;
		while (run_str[i])
		{
			if (run_str[i] == '\'' || run_str[i] == '\"')
				count_q++;
			i++;
		}
		ft_strdel(&run_str);
		run_str = (ft_strnew(i + count_q));
		i = 0;
		count_q = 0;
		while (tmp[i])
		{
			if (tmp[i] == '\'' || tmp[i] == '\"')
				run_str[count_q++] = '\\';
			run_str[count_q++] = tmp[i++];
		}
	}
	else if (i && i < 3)
	{
//		ft_putendl(": bad substitution");
//		ft_strdel(str);
		return (1);
	}
	run_str = convert_backslash(run_str);
	expand_transformer(&run_str, 1);
	g_tracking.mysh->in_here = 0;
	run_str = convert_back(run_str);
	run_str = remove_back(run_str);
	if (g_tracking.mysh->err_expend || !run_str)
		return (1);
	ft_strdel(str);
	*str = run_str;
	return (0);
}
