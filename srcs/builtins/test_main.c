/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 03:02:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/17 03:15:38 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sh42.h"

char	**copy_tab_minus_one(int argc, char **argv)
{
	char	**av;
	int		i;
	int		a;

	i = 1;
	a = 0;
	av = malloc(sizeof(char *) * (argc + 1));
	while (argv[i])
	{
		av[a] = ft_strdup(argv[i]);
		i++;
		a++;
	}
	av[a] = NULL;
	return (av);
}

int		one_arg(char **argv)
{
	if (argv[0])
		return (0);
	else
		return (1);
}

int		test_parse(int argc, char **argv)
{
	if (argc == 0)
		return (1);
	if (argc == 1)
		return (one_arg(argv));
	if (argc == 2)
		return (two_arg(argv));
	if (argc == 3)
		return (three_arg(argv));
	ft_putendl_fd("Too many arguments", 2);
	return (-1);
}

int		reverse(int i, int flag)
{
	if (flag == -1)
	{
		if (i == 1)
			return (0);
		if (i == 0)
			return (1);
	}
	return (i);
}

int		count_arg(char **taab)
{
	int		i;

	i = 0;
	if (!taab)
		return (1);
	while (taab[i])
		i++;
	return (i);
}

int		main_test(void)
{
	int		flag;
	int		i;
	int		argc;
	char	**argv;
	char	**not;

	flag = 1;
	not = NULL;

	argc = count_arg(g_tracking.g_tab_exec);
	argv = g_tracking.g_tab_exec;
	argv = copy_tab_minus_one(argc, argv);
	argc--;
	if (argc < 1)
		return (1);
	if (ft_strcmp(argv[0], "!") == 0)
	{
		not = copy_tab_minus_one(argc, argv);
		free_tab(argv);
		argc--;
		argv = not;
		flag = -1;
	}
	i = test_parse(argc, argv);
	i = reverse(i, flag);
	ft_putnbr(i);
	ft_putchar('\n');
	free_tab(argv);
	return (0);
}