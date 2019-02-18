/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:43:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/18 17:46:19 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	history_builtin_s(t_core *core)
{
	int i;
	int j;
	int h;
	char *tmp;

	i = 2;
	j = 0;
	h = 0;
	if (!(core->arg[i]))
		return ;
	else
	{
		while (core->hist->next)
			core->hist = core->hist->next;
		if (core->hist->previous)
		{
			core->hist = core->hist->previous;
			hist_delete_index(core->hist, core->hist->index);
		}
		else
			hist_free(core->hist);
	}
	i = 0;
	while (core->arg[i])
	{
		while (core->arg[i][j])
			j++;
		i++;
	}
	tmp = malloc(sizeof(char) * (j + i-2)+1);
	i = 2;
	while (core->arg[i])
	{
		while (core->arg[i][j])
			tmp[h++] = core->arg[i][j++];
		i++;
		if (core->arg[i])
			tmp[h++] = ' ';
		tmp[h] = 0;
	}
	ft_putendl(tmp);
}