/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 03:49:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temporal_env.h"
#include "sh21.h"

void		check_if_resetenv(void)
{
	t_tmpenv	*tmp;
	t_resetenv	*hold;

	hold = g_tracking.mysh->resetenv;
	while (hold && hold->cmdindex != g_tracking.cmdindex)
		hold = hold->next;
	if (hold && hold->cmdindex == g_tracking.cmdindex && hold->resetenv == 1)
		free_env();
	tmp = g_tracking.mysh->tmpenv;
	if (tmp)
	{
		while (tmp && tmp->cmdindex != g_tracking.cmdindex)
			tmp = tmp->next;
		if (tmp && tmp->cmdindex == g_tracking.cmdindex)
		{
			g_tracking.mysh->envsave = copyenv();
			while (tmp && tmp->cmdindex == g_tracking.cmdindex)
			{
				set_tmp_env(tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
	}
}

void		reset_tmpenv(void)
{
	t_tmpenv	*hold;
	t_tmpenv	*tmp;

	tmp = g_tracking.mysh->tmpenv;
	if (tmp)
	{
		while (tmp->next)
		{
			hold = tmp->next;
			ft_strdel(&tmp->value);
			ft_strdel(&tmp->key);
			ft_free(tmp);
			tmp = hold;
		}
		ft_strdel(&tmp->value);
		ft_strdel(&tmp->key);
		ft_free(tmp);
	}
	g_tracking.mysh->tmpenv = NULL;
}

char		*clean_line_tmpenv(char *str, int jsave, int save)
{
	int		len;

	while (is_spaces(str, jsave, 2))
		jsave++;
	len = jsave;
	jsave = skip_tmp_env(str, jsave, 0);
	save = jsave;
	while (str[jsave] != '\0')
	{
		len++;
		jsave++;
	}
	return (clean_line_tmp_helper(len, str, save));
}

char		*tmp_env_namemaker(char *str, int start)
{
	char	*new;
	int		len;
	int		save;

	save = start;
	len = 0;
	while (str[save] != '\0' && str[save] != '=' && !is_spaces(str, save, 1))
	{
		len++;
		save++;
	}
	if (!(new = ft_malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (str[start] != '\0' && str[start] != '=' && !is_spaces(str, start, 1))
	{
		new[len] = str[start];
		len++;
		start++;
	}
	new[len] = '\0';
	return (new);
}

int			is_env_alone_check_helper(char *str, int jsave, int isave)
{
	int		count;

	while (is_spaces(str, jsave, 2))
		jsave++;
	while (str[jsave])
	{
		count = 0;
		if (!is_spaces(str, jsave, 2))
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
		if (count == 1 && !is_spaces(str, isave, 1))
			return (0);
		if (str[jsave])
			jsave++;
	}
	return (1);
}
