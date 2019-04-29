/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 09:32:31 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_last		*find_tmpenv_vars(t_last *begin)
{
	return (begin);
}

int			check_if_env(char *str, int i)
{
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	if (str[i] == '=' && i > 0 && str[i + 1] && !is_spaces(str, i - 1, 1)
			&& !is_spaces(str, i + 1, 1))
		return (2);
	return (0);
}

t_last		*tmp_local_vars(t_last *begin, t_last *beginsave)
{
	int		mode;

	g_tracking.mysh->tmpenvsave = NULL;
	g_tracking.mysh->setsave = NULL;
	if ((mode = check_if_env(begin->name, 0)))
	{
		begin = begin->next;
		while (begin)
		{
			if (!check_if_env(begin->name, 0))
			{
				mode = 1;
				break ;
			}
			begin = begin->next;
		}
		if (mode == 1)
			return (find_tmpenv_vars(beginsave));
		// else
		// 	return (find_set_vars(beginsave));
	}
	return (beginsave);
}

// void		apply_tmpenv(void)
// {
// 	t_tmpenv	*tmp;

// 	tmp = g_tracking.mysh->tmpenv;
// 	if (tmp)
// 	{
// 		while (tmp && tmp->cmdindex != g_tracking.cmdindex)
// 			tmp = tmp->next;
// 		if (tmp && tmp->cmdindex == g_tracking.cmdindex)
// 		{
// 			while (tmp && tmp->cmdindex == g_tracking.cmdindex)
// 			{
// 				set_tmp_env(tmp->key, tmp->value);
// 				tmp = tmp->next;
// 			}
// 		}
// 	}
// }

// void		free_env(void)
// {
// 	free_keyval(g_tracking.mysh->env);
// 	g_tracking.mysh->env = NULL;
// }
