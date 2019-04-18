/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 06:00:48 by mjose             #+#    #+#             */
/*   Updated: 2019/04/08 06:11:00 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		return_loop(int i, char *str)
{
	if (check(str) == 1 || i == 12 || i == 6)
		ft_free(str);
	else
		add_to_str(str);
	is_still_atty();
	return (0);
}

int		readloop(int i, int fd)
{
	char	c;
	char	*str;

	str = ft_strnew(0);
	if ((read(fd, &c, 1)) == 0)
		ft_exit2(EXIT_SUCCESS);
	str = ft_strjoinchar(str, c, 1);
	i = single_key(c);
	if (i == 13 || i == 10)
	{
		ft_free(str);
		return (1);
	}
	if (c < 32 && i != 12)
	{
		while (42)
		{
			read(fd, &c, 1);
			str = ft_strjoinchar(str, c, 1);
			i = is_cmd(str);
			if (i >= 6)
				break ;
		}
	}
	return (return_loop(i, str));
}
