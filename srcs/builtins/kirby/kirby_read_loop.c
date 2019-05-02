/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kirby_read_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 00:44:06 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 06:55:58 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		rand_loop(int time)
{
	fd_set			setfd;
	struct timeval	tv;
	int				retval;
	char			c;

	while (1)
	{
		FD_ZERO(&setfd);
		FD_SET(0, &setfd);
		tv.tv_sec = time;
		tv.tv_usec = 0;
		retval = select(0 + 1, &setfd, NULL, NULL, &tv);
		if (retval == 0)
		{
			print_box(2);
			return (0);
		}
		if (FD_ISSET(0, &setfd))
		{
			read(STDERR_FILENO, &c, 1);
			return (too_soon(c));
		}
	}
}

int		generate_rand(void)
{
	int		random;

	random = 0;
	while (random < 10000)
	{
		srand(time(NULL));
		random = rand() % 13;
	}
	return (random);
}

int		read_samurai(void)
{
	char	c;

	write(2, "\a", 1);
	write(2, "\a", 1);
	c = 0;
	print_box(3);
	read(0, &c, 1);
	if (c == 27)
		return (1);
	if (c == 115)
		return (duel(1));
	if (c == 108)
		return (duel(2));
	return (0);
}
