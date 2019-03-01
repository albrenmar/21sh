/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lib_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:31:10 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/01 16:47:34 by hdufer           ###   ########.fr       */
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

t_hist		*builtin_s_args(char **tab, t_hist *hist)
{
	int i;
	int j;
	int h;
	char *str_ret;

	i = 0;
	j = 0;
	h = 0;
	while(tab[i])
	{
		j = 0;
		while(tab[i][j])
			j++;
		i++;
	}
	str_ret = ft_memalloc(sizeof(char) * j+i + 1);
	i = 0;
	j = 0;
	while(tab[i])
	{
		j = 0;
		while(tab[i][j])
			str_ret[h++] = tab[i][j++];
		i++;
		if (tab[i])
			str_ret[h++] = ' ';
	}
	str_ret[h] = '\0';
	if (hist)
		hist_lst_add_next(hist, ft_strdup(str_ret));
	else
		hist = hist_lst_create(str_ret);
	return hist;
}