/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lib_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:31:10 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/24 14:51:46 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_isdigit_str(char* str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char		*builtin_s_args(char **tab)
{
	int i;
	int j;
	int h;
	char *str_ret;

	i = 2;
	j = 0;
	h = 0;
	while(tab[i])
	{
		while(tab[i][j])
			j++;
		i++;
	}
	str_ret = ft_memalloc(sizeof(char) * j+(i-2) + 1);
	i = 2;
	j = 0;
	while(tab[i])
	{
		while(tab[i][j])
			str_ret[h++] = tab[i][j++];
		i++;
		if (tab[i+1])
			str_ret[h++] = ' ';
	}
	str_ret[h] = '\0';
	return str_ret;
}