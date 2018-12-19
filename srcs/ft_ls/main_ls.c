/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 22:58:59 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/19 01:00:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer		*modified_ls(int argc, char **argv)
{
	int				i;
	char			*str;
	int				flag;
	int				called;
	t_lstcontainer	*liste;

	i = 1;
	flag = 0;
	called = 0;
	str = ft_strnew(1);
	if (argc == 1)
	{
		liste = ft_ls(".", "", 0);
		free(str);
		return (liste);
	}
	i = ft_option(argv, &str, &flag);
	while (argc > i && flag != 1)
	{
		liste = ft_ls(argv[i], str, called);
		i++;
		called = 1;
	}
	free(str);
	return (liste);
}
