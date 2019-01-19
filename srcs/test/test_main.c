/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 03:02:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/18 04:24:32 by bsiche           ###   ########.fr       */
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

char	*get_perm(char *filename)
{
	t_lstcontainer	*liste;
	char			**taab;
	t_ls 			*new_ls;
	char			*test;
	t_list			*buf;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = filename;
	liste = modified_ls(2, taab);
	if (!buf)
		return (NULL);
	buf = ft_lstgetfirst(liste->firstelement);
	new_ls = buf->content;
	test = new_ls->strpermission;
	return (test);
}

int		one_arg(char **argv)
{
	if (argv[0])
		return (0);
	else
		return (1);
}

int		two_arg(char **argv)
{
	if (argv[0][0] != '-')
		return (1);
	if (argv[0][1] >= 'b' && argv[0][1] <= 'g')
		return (0);
	return (0);
}

int		test_parse(int argc, char **argv)
{
	if (argc == 0)
		return (1);
	if (argc == 1)
		return (one_arg(argv));
	if (argc == 2)
		return (two_arg(argv));
/*	if (argc = 3)
		return (three_arg(argv));
	if (argc = 4)
		return (four_arg(argv));
	if (argc = 5)
	
			return (five_arg(argv));*/
	ft_putendl("fail");
	return (-1);
}

int		main_test(int argc, char **argv)
{
	int	flag;
	int	i;
	char	**newtab;

	flag = 0;
	if (argc == 1)
		return (1);
//	newtab = copy_tab_minus_one(argc, argv);
	i = 0;
	argc--;
//	test_parse(argc, newtab);
	ft_putendl(argv[1]);
	get_perm(argv[1]);
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
	ft_putnbr(argc);
	ft_putchar('\n');
	return(0);
}