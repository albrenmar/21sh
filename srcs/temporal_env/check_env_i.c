/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/09 02:37:38 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		add_reset_env(int cmdindex)
{
	t_resetenv	*tmp;

	tmp = g_tracking.mysh->resetenv;
	if (g_tracking.mysh->resetenv == NULL)
	{
		if (!(g_tracking.mysh->resetenv = ft_malloc(sizeof(t_tmpenv))))
			return ;
		tmp = g_tracking.mysh->resetenv;
		tmp->cmdindex = cmdindex;
		tmp->resetenv = 1;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = ft_malloc(sizeof(t_tmpenv))))
			return ;
		tmp = tmp->next;
		tmp->cmdindex = cmdindex;
		tmp->resetenv = 1;
	}
	tmp->next = NULL;
}

char		*env_i_h(char *str, int j, int cmdi)
{
	int		jsave;

	jsave = j + 1;
	add_reset_env(cmdi);
	str = clean_env_i(str, jsave);
	if (only_spaces_and_sep(str))
		str = swap_tmpenv_for_true(str, 0);
	return (str);
}

int			check_if_env_i_alone(char *str, int i, int count)
{
	while (i != 0 && str[i] != 'e')
		i--;
	if (i == 0)
		return (1);
	i--;
	while (i > 0)
	{
		while (i > 0 && is_spaces(str, i, 2))
			i--;
		if (i > 0 && !is_spaces(str, i, 2))
		{
			while (i > 0 && !is_spaces(str, i, 2))
			{
				if (str[i] == '=' && str[i - 1] && !is_spaces(str, i - 1, 2))
					count++;
				i--;
			}
			if (count == 0)
				return (0);
		}
		count = 0;
		if (i > 0)
			i--;
	}
	return (1);
}

char		*get_last_env_i(char **taab, int i, int j, int cmdi)
{
	while (j + 5 < (int)ft_strlen(taab[i]))
	{
		if (taab[i][j] == 'e' && taab[i][j + 1] == 'n' && taab[i][j + 2] == 'v'
		&& taab[i][j + 3] == ' ')
		{
			j = j + 3;
			while (taab[i][j] == ' ')
				j++;
			if (taab[i][j] && taab[i][j + 1] && taab[i][j] == '-'
			&& taab[i][j + 1] == 'i' && (taab[i][j + 2] == '\0'
			|| is_spaces(taab[i], j + 2, 1)))
			{
				if (check_if_env_i_alone(taab[i], j, 0))
				{
					taab[i] = env_i_h(taab[i], j, cmdi);
					j = 0;
				}
				else
					return (taab[i]);
			}
		}
		j++;
	}
	return (taab[i]);
}

char		*check_if_env_option_i(char **taab, int i, int j, int cmdi)
{
	taab[i] = get_last_env_i(taab, i, j, cmdi);
	while (taab[i][j] && is_spaces(taab[i], j, 2))
		j++;
	while (taab[i][j] && !is_spaces(taab[i], j, 1) && taab[i][j] != '=')
		j++;
	if (taab[i][j] == '=' && j && !is_spaces(taab[i], j - 1, 2))
		taab[i] = swap_env_var(taab[i], j, cmdi);
	return (taab[i]);
}
