/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 03:49:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temporal_env.h"
#include "sh21.h"

char			*refactor_line_sep(char *line, int i)
{
	char		*new;
	int			len;
	int			isave;

	len = 0;
	while (line[i] && (line[i] == '&' || line[i] == ';'))
		i++;
	isave = i;
	while (line[i])
	{
		i++;
		len++;
	}
	if (!(new = ft_malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (line[isave] != '\0')
	{
		new[len] = line[isave];
		len++;
		isave++;
	}
	new[len] = '\0';
	ft_strdel(&line);
	return (new);
}

char			*check_first_char_sep(char *line)
{
	int			i;

	i = 0;
	while (line[i] && is_spaces(line, i, 1))
		i++;
	if (line[i] && (line[i] == '&' || line[i] == '|' || line[i] == ';'))
	{
		if (line[i] == '&' || line[i] == ';')
			return (refactor_line_sep(line, i));
		else
		{
			while (line[i] && line[i] != ';' && line[i] != '&')
				i++;
			if (!line[i])
			{
				ft_strdel(&line);
				return (ft_strdup(" "));
			}
			else
				return (refactor_line_sep(line, i));
		}
	}
	return (line);
}

int				next_separator_env(char *str, int i, int save)
{
	if (i == 0)
	{
		while (str[i])
		{
			i++;
			if ((str[i] == '&' && str[i + 1] && (str[i + 1] == '&'
			|| is_spaces(str, i + 1, 1))) || str[i] == ';' || str[i] == '|')
				return (i);
		}
	}
	else
	{
		save = i;
		while (str[i] && (str[i] == '&' || str[i] == ';' || str[i] == '|'))
			i++;
		while (str[i])
		{
			i++;
			if ((str[i] == '&' && str[i + 1] && (str[i + 1] == '&'
			|| is_spaces(str, i + 1, 1))) || str[i] == ';' || str[i] == '|')
				return (i);
		}
	}
	return (i);
}

char			*add_tmp_var(char *str, int save, int i)
{
	char	*dest;
	int		j;

	if (!(dest = ft_malloc(sizeof(char) * i - save + 1)))
		return (NULL);
	j = 0;
	while (save < i)
	{
		dest[j] = str[save];
		save++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

void			init_tmp_env(char *str, int jsave, int save, int cmdindex)
{
	t_tmpenv	*tmp;

	tmp = g_tracking.mysh->tmpenv;
	if (g_tracking.mysh->tmpenv == NULL)
	{
		if (!(g_tracking.mysh->tmpenv = ft_malloc(sizeof(t_tmpenv))))
			return ;
		tmp = g_tracking.mysh->tmpenv;
		tmp->cmdindex = cmdindex;
		tmp->key = tmp_env_namemaker(str, jsave);
		tmp->value = tmp_env_namemaker(str, save + 1);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = ft_malloc(sizeof(t_tmpenv))))
			return ;
		tmp = tmp->next;
		tmp->cmdindex = cmdindex;
		tmp->key = tmp_env_namemaker(str, jsave);
		tmp->value = tmp_env_namemaker(str, save + 1);
	}
	tmp->next = NULL;
}
