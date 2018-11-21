/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 00:52:08 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/16 21:45:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int     is_key(char *str)
{
    int	i;
    int	flag;

	i = 0;
	flag = 0;
	while () 

}


int		exec_key(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i > 3)
		return (3);
	if (K_RIGHT || K_LEFT || K_UP || K_DOWN)
		return (ft_cursor(str));
	if (K_RT)
	{
		exit(0);
		return (1);
	}
	return (0);
}