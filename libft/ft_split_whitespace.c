/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 05:38:49 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/06 05:47:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_white(char *str)
{
	char	**tab;
	char	*newstr;
	int		i;

	tab = ft_strsplit(str, '\t');
	i = 0;
	newstr = ft_strnew(0);
	while (tab[i])
	{
		newstr = ft_strjoin(newstr, tab[i], 1);
		newstr = ft_strjoin(newstr, " ", 1);
		i++;
	}
	i = 0;
	free_tab(tab);
	tab = ft_strsplit(newstr, ' ');
	free(newstr);
	return (tab);
}
