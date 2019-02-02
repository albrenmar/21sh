/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 02:50:02 by mjose             #+#    #+#             */
/*   Updated: 2019/02/02 05:04:28 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*recup_expath(char **tab)
{
	int		i;
	char	*path;

	i = 1;
	path = ft_strnew(1);
	while (tab[i])
	{
		tab[i] = ft_strjoinfree("/", tab[i], 2);
		path = ft_strdup(ft_strjoinfree(path, tab[i++], 3));
	}
	return (path);
}

void	expand_tilde_user(char **str, t_expand **expand)
{
	char	*user;
	char	*tmp_path;
	char	**tmp;
	char	*home;

	tmp_path = NULL;
	if (!ft_strchr(*str, '/'))
		user = ft_strdup(*str + 1);
	else
	{
		tmp = ft_strsplit(*str, '/');
		tmp_path = tmp[0];
		user = ft_strndup(tmp_path + 1, ft_strlen(tmp_path + 1));
		tmp_path = recup_expath(tmp);
	}
	home = get_user_home(user);
	ft_strdel(str);
	if (!tmp_path)
		*str = home;
	else
		*str = ft_strjoinfree(home, tmp_path, 3);
}

void	expand_tilde_path(char **str, t_expand **expand)
{
	char	*home;
	char	*str_tmp;

	home = get_home_value();
	str_tmp = ft_strjoinfree(home, *str + 1, 1);
	ft_strdel(str);
	*str = str_tmp;
	update_list_expand(expand, str);
}

void	expand_tilde_only(char **str)
{
	ft_strdel(str);
	*str = get_home_value();
}
