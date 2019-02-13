/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_percent_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:33:22 by mjose             #+#    #+#             */
/*   Updated: 2019/02/13 05:42:39 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	select_not_found(char **str, char *value_var, char *to_srch)
{
	int		total_found;
	char	*tmp;
	int		i;

	total_found = ft_strlen(to_srch);
	i = 0;
	ft_strdel(str);
	tmp = value_var;
	while (total_found != i++)
		tmp++;
	*str = ft_strrev(tmp, 0);
}
