/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:29:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 01:20:34 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int					check_forbidden_char(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '-' || str[i] == '/'
		|| str[i] == '~')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		ft_putstr("forbidden char in alias : ");
		ft_putendl(str);
	}
	return (flag);
}

t_lstcontainer		*alias_error(char *alias)
{
	t_lstcontainer	*split;
	t_list			*tmp;
	char			*alias_test;

	if (!alias)
		return (NULL);
	split = ft_strsplitlst(alias, '=');
	if (lstcontainer_size(split) < 2)
	{
		ft_putstr("Wrong alias : ");
		ft_putendl(alias);
		ft_putendl("Usage: Alias [alias]=[cmd]");
		ft_freesplitlist(split);
		return (NULL);
	}
	tmp = split->firstelement;
	alias_test = tmp->content;
	if ((check_forbidden_char(alias_test) != 0))
	{
		ft_freesplitlist(split);
		return (NULL);
	}
	unalias(split->firstelement->content);
	return (split);
}

t_keyval			*parse_alias(char *alias)
{
	t_lstcontainer	*split;
	t_keyval		*al_to_add;
	t_list			*tmp;

	al_to_add = NULL;
	split = alias_error(alias);
	if (!split || !(al_to_add = ft_malloc(sizeof(struct s_keyval))))
		return (NULL);
	tmp = split->firstelement;
	al_to_add->key = ft_strdup(tmp->content);
	tmp = tmp->next;
	al_to_add->value = NULL;
	while (tmp)
	{
		if (!al_to_add->value)
			al_to_add->value = ft_strnew(0);
		al_to_add->value = ft_strjoinfree(al_to_add->value, tmp->content, 1);
		tmp = tmp->next;
	}
	ft_freesplitlist(split);
	return (al_to_add);
}

int					add_alias(void)
{
	t_lstcontainer	*alias_lst;
	t_keyval		*alias_to_add;
	char			**av;
	char			*alias;

	av = g_tracking.g_tab_exec;
	if (!av[1])
	{
		print_alias_lst();
		return (0);
	}
	alias = ft_strdup(av[1]);
	alias_lst = g_tracking.mysh->alias_lst;
	alias_to_add = parse_alias(alias);
	ft_strdel(&alias);
	if (alias_lst && alias_to_add)
		lstcontainer_add(alias_lst, alias_to_add);
	return (0);
}
