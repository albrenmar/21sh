/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/09 01:39:54 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temporal_env.h"
#include "sh21.h"

char		*check_if_swap_helper(char **taab, int i, char *line)
{
	char	*new;

	new = NULL;
	while (taab[i] != NULL)
	{
		if (new != NULL)
			new = ft_strjoinfree(new, taab[i], 1);
		else
			new = ft_strdup(taab[i]);
		i++;
	}
	free_tab(taab);
	ft_strdel(&line);
	return (new);
}

void		set_tmp_env(char *key, char *value)
{
	t_list		*hold;
	t_list		*save;
	t_keyval	*tmp;

	hold = NULL;
	if (g_tracking.mysh->env)
		hold = ft_lstgetfirst(g_tracking.mysh->env->firstelement);
	while (hold)
	{
		tmp = hold->content;
		if (!ft_strcmp(key, tmp->key))
		{
			replace_env_str(key, value);
			return ;
		}
		save = hold;
		hold = hold->next;
	}
	ft_add_env_string(key, value);
}

int			skip_tmp_env(char *str, int jsave, int isave)
{
	int		count;

	while (str[jsave] && is_spaces(str, jsave, 2))
		jsave++;
	while (str[jsave])
	{
		count = 0;
		if (!is_spaces(str, jsave, 1))
		{
			isave = jsave;
			count = 1;
		}
		while (str[jsave] && !is_spaces(str, jsave, 1))
		{
			if (str[jsave] == '=')
				count++;
			jsave++;
		}
		if (count == 1 && (!str[jsave]
		|| (str[jsave] && is_spaces(str, jsave, 2))))
			return (isave);
		if (str[jsave])
			jsave++;
	}
	return (0);
}

int			save_tmp_env_helper(int jsave, char *str, int cmdindex, int hold)
{
	int		megahold;

	megahold = jsave;
	if (jsave > 0)
		jsave--;
	while (jsave > 0 && !is_spaces(str, jsave, 1))
		jsave--;
	if (jsave > 0 || (jsave == 0 && is_spaces(str, jsave, 2)))
		jsave++;
	init_tmp_env(str, jsave, hold, cmdindex);
	return (megahold);
}

void		save_tmp_env(char *str, int jsave, int cmdindex)
{
	int		count;
	int		hold;

	while (is_spaces(str, jsave, 2))
		jsave++;
	while (str[jsave])
	{
		count = 0;
		while (str[jsave] && !is_spaces(str, jsave, 1))
		{
			if (str[jsave] == '=')
			{
				hold = jsave;
				count++;
			}
			jsave++;
		}
		if (str[jsave] && count != 0 && !is_spaces(str, jsave - 1, 1))
			jsave = save_tmp_env_helper(jsave, str, cmdindex, hold);
		if (str[jsave])
			jsave++;
	}
}
