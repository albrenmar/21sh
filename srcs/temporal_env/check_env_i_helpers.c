/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_i_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/14 23:30:45 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*swap_tmpenv_for_true(char *str, int i)
{
	char	*new;

	if (str[i])
	{
		while (str[i] != '\0' && (str[i] == '&' || str[i] == '|'
		|| str[i] == ';'))
			i++;
		if (!(new = ft_malloc(sizeof(char) * i + 1)))
			return (NULL);
		i = 0;
		while (str[i] != '\0' && (str[i] == '&' || str[i] == '|'
		|| str[i] == ';'))
		{
			new[i] = str[i];
			i++;
		}
		new[i] = '\0';
		new = ft_strjoinfree(new, " true ", 1);
		ft_strdel(&str);
		return (new);
	}
	ft_strdel(&str);
	return (ft_strdup(" true "));
}

int			only_spaces_and_sep(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v'
		&& str[i] != '&' && str[i] != '|' && str[i] != ';' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

char		*clean_env_i_helper(char *new, char *str, int i, int js)
{
	while (str[i] && is_spaces(str, i, 2))
	{
		new[i] = str[i];
		i++;
	}
	js = js + 1;
	while (str[js])
	{
		new[i] = str[js];
		js++;
		i++;
	}
	new[i] = '\0';
	ft_strdel(&str);
	return (new);
}

char		*clean_env_i(char *str, int js)
{
	int		len;
	int		i;
	char	*new;

	len = 0;
	i = 0;
	while (str[i] && is_spaces(str, i, 2))
	{
		len++;
		i++;
	}
	if (len == 0)
		len = ft_strlen(str) - js;
	else
		len = ft_strlen(str) - js + len;
	if (!(new = ft_malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	return (clean_env_i_helper(new, str, i, js));
}

void		reset_resetenv(void)
{
	t_resetenv	*hold;
	t_resetenv	*tmp;

	tmp = g_tracking.mysh->resetenv;
	if (tmp)
	{
		while (tmp->next)
		{
			hold = tmp->next;
			ft_free(tmp);
			tmp = hold;
		}
		ft_free(tmp);
	}
	g_tracking.mysh->resetenv = NULL;
}
