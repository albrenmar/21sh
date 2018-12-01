/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:12:58 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/28 23:26:37 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		main(void)
{
	char	*prompt;
	pid_t	father;
	char 	*argv[]={"ls",NULL};
	int		i;

	cursorinit();
	ft_siginit();
//	ft_putstr(">");
	get_term();
	get_key();
	return (0);
}
