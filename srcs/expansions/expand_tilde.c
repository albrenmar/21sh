/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 02:50:02 by mjose             #+#    #+#             */
/*   Updated: 2019/02/02 02:51:45 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

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
