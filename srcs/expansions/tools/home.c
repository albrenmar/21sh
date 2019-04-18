/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 01:20:02 by mjose             #+#    #+#             */
/*   Updated: 2019/04/08 05:17:44 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh21.h"

char	*get_user_home(char *user)
{
	struct passwd	*user_inf;
	char			*home_dir;

	user_inf = getpwnam(user);
	home_dir = ft_strdup(user_inf->pw_dir);
	return (home_dir);
}

char	*get_home_value(void)
{
	char	*home;

	home = NULL;
	if ((home = get_env_string("HOME")) && ft_strequ(home, ""))
		return (ft_strdup(home));
	else if ((home = get_parm_string("HOME")) && ft_strequ(home, ""))
		return (ft_strdup(home));
	else
		return (get_user_home(getlogin()));
	return (NULL);
}
