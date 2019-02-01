/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 02:50:02 by mjose             #+#    #+#             */
/*   Updated: 2019/02/01 07:00:42 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	expand_path_tilde_path(char **str, t_expand **expand, int i)
{
	char	*home;
	char	*str_tmp1;
	char	*str_tmp2;

	home = get_user_home(getlogin());
	str_tmp1 = ft_strsub(*str, 0, i - 2, 0);
	str_tmp2 = ft_strsub(*str, i, (*expand)->len - i, 1);
	str_tmp1 = ft_strjoinfree(str_tmp1, ft_strjoinfree(home, str_tmp2, 3), 3);
	*str = str_tmp1;
	update_list_expand(expand, str);
}

void	expand_tilde_path(char **str, t_expand **expand)
{
	char	*home;
	char	*str_tmp;

	home = get_user_home(getlogin());
	str_tmp = ft_strjoinfree(home, *str + 1, 1);
	ft_strdel(str);
	*str = str_tmp;
	update_list_expand(expand, str);
}

void	expand_tilde_only(char **str)
{
	char			*login;
	struct passwd	*user_inf;

	login = getlogin();
	ft_strdel(str);
	user_inf = getpwnam(login);
	*str = ft_strdup(user_inf->pw_dir);
}
