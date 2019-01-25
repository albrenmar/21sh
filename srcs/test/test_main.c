/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 03:02:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/20 20:53:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sh42.h"

char	**copy_tab_minus_one(int argc, char **argv)
{
	char	**newtab;
	int		i;
	int		a;

	i = 1;
	a = 0;
	newtab = malloc(sizeof(char *) * (argc + 1));
	while (argv[i])
	{
		newtab[a] = ft_strdup(argv[i]);
		i++;
		a++;
	}
	newtab[a] = NULL;
	return (newtab);
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

int		main_test(int argc, char **argv)
{
	int		flag;
	int		i;
	char	**newtab;
	char	**not;

	flag = 1;
	not = NULL;
	i = -1;
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		free_tab(argv);
		exit(0);
	}
	if (argc == 1)
		return (1);
	newtab = copy_tab_minus_one(argc, argv);
	argc--;
	if (ft_strcmp(argv[0], "!") == 0)
	{
		not = copy_tab_minus_one(argc, newtab);
		free_tab(newtab);
		argc--;
		flag = -1;
	}
	i = test_parse(argc, newtab);
	i = reverse(i, flag);
	ft_putnbr(i);
	ft_putchar('\n');
	free_tab(newtab);
	free_tab(argv);
	return (0);
}

int		ft_build_test(char *string)
{
	char	**argv;
	int		argc;

	argv = ft_strsplit(string, ' ');
	argc = 0;
	while (argv[argc])
		argc++;
	main_test(argc, argv);
	return (0);
}