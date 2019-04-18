/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*aliased_line(char **taab, int i, int j)
{
	char	*new;

	new = NULL;
	while (taab[i])
	{
		taab[i] = check_if_first_word_alias(taab[i], j, 0);
		i++;
	}
	i = 0;
	while (taab[i])
	{
		if (new != NULL)
			new = ft_strjoinfree(new, taab[i], 1);
		else
			new = ft_strdup(taab[i]);
		i++;
	}
	return (new);
}

void		alias_swapper_helper(int i, int j, char *line, char **taab)
{
	int		hold;
	int		l;

	while (i < (int)ft_strlen(line))
	{
		hold = i;
		i = next_separator(line, i);
		if (!(taab[j] = ft_malloc(sizeof(char) * i + 1)))
			return ;
		l = 0;
		while (hold < i)
		{
			taab[j][l] = line[hold];
			l++;
			hold++;
		}
		taab[j][l] = '\0';
		j++;
	}
	taab[j] = NULL;
}

char		*alias_swapper(char *line, int i, int count)
{
	char	**taab;
	int		j;

	i = 0;
	count = 0;
	while (line[i])
	{
		i = next_separator(line, i);
		count++;
		if (line[i])
		{
			i++;
			if (line[i] == '\0')
				count++;
		}
	}
	if (!(taab = ft_malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	alias_swapper_helper(i, j, line, taab);
	ft_strdel(&line);
	line = aliased_line(taab, 0, 0);
	free_tab(taab);
	return (line);
}

void		print_alias_lst(void)
{
	t_keyval		*tmp;
	t_list			*buf;

	buf = NULL;
	if (g_tracking.mysh->alias_lst)
		buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (tmp->key)
				ft_putstr(tmp->key);
			ft_putchar('=');
			if (tmp->value)
				ft_putendl(tmp->value);
		}
		buf = buf->next;
	}
}

char		*return_alias(char *name)
{
	t_keyval		*tmp;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst || !name)
		return (NULL);
	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (ft_strcmp(tmp->key, name) == 0)
				return (tmp->value);
		}
		buf = buf->next;
	}
	return (NULL);
}
