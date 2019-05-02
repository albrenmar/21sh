/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kirby_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 04:57:22 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		too_soon(char buf)
{
	if (buf == 'l')
	{
		ft_putendl_fd("Player 2 drew too soon. P1 WINS !", 2);
		sleep(2);
	}
	if (buf == 's')
	{
		ft_putendl_fd("Player 1 drew too soon. P2 WINS !", 2);
		sleep(2);
	}
	if (set_kirby_screen() != 0)
		return (-1);
	if (buf == 27)
		return (-1);
	return (-3);
}

int		print_usage(void)
{
	char	c;

	c = 65;
	ft_putendl("Player one press: s");
	ft_putendl("Player one press: l");
	ft_putendl("press enter to start a new game");
	while (c != 10 && c != 27)
		read(0, &c, 1);
	if (c == 10)
		return (0);
	if (c == 27)
		return (1);
	return (1);
}

int		game_loop(void)
{
	int		i;

	if (set_kirby_screen() != 0)
		return (-1);
	if (print_usage() == 1)
		return (1);
	if (set_kirby_screen() != 0)
		return (-1);
	print_file(1);
	print_box(0);
	i = rand_loop(1);
	if (i == -3)
		return (0);
	if (i == -1)
		return (1);
	return (read_samurai());
}

int		k_main(void)
{
	int		flag;

	flag = 0;
	if (g_tracking.interactive != 1)
		return (0);
	if (test_exist_dir("/tmp/kirby") == -1)
	{
		ft_putendl("could not open source dir");
		return (2);
	}
	tcsetattr(0, TCSANOW, &g_tracking.myterm);
	tputs(tgetstr("vi", NULL), 1, yan_putchar);
	tputs(tgetstr("ti", NULL), 1, yan_putchar);
	while (game_loop() == 0)
	{
	}
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
	tputs(tgetstr("te", NULL), 1, yan_putchar);
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	if (flag == -1)
		ft_putendl_fd("Temsize too small", 2);
	if (flag < 0)
		return (2);
	return (0);
}
