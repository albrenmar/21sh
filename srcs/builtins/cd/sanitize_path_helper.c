/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_path_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:54:20 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 02:16:45 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*check_multi_slash(char *path)
{
	char	*new_path;
	int		i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i] && path[i] == '/')
		i++;
	new_path = ft_strdup(path + (i - 1));
	ft_strdel(&path);
	return (new_path);
}
