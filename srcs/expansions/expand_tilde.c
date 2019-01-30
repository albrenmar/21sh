/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 02:50:02 by mjose             #+#    #+#             */
/*   Updated: 2019/01/30 06:21:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	expand_tilde_only(char **str)
{
	char			*login;
	struct passwd	*user_inf;

	login = getlogin();
	ft_strdel(str);
	user_inf = getpwnam(login);
	*str = ft_strdup(user_inf->pw_dir);
}
