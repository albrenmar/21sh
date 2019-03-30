/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_delete_multiple.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thegenius <thegenius@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:39:57 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/30 14:11:29 by thegenius        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			delete_dispatch_multiple(int first_i, int second_i)
{
	long tmp_min;
	long tmp_big;

	tmp_min = (first_i < second_i) ? first_i : second_i;
	tmp_big = (first_i > second_i) ? first_i : second_i;
	if (first_i > 0)
		if (search_index_to_delete(first_i) == 0)
			return (0);
	if (first_i < 0)
		if (search_index_to_delete_neg(first_i) == 0)
			return (0);
	if (second_i > 0)
		if (search_index_to_delete(second_i) == 0)
			return (0);
	if (second_i < 0)
		if (search_index_to_delete_neg(second_i) == 0)
			return (0);
	if (first_i == second_i && first_i > 0 && second_i > 0)
		return (delete_index(first_i));
	if (first_i == second_i && first_i < 0 && second_i < 0)
		return (delete_index_neg(first_i));
	if (first_i > 0 && second_i > 0)
	{
		while (tmp_min <= tmp_big)
		{
			if (search_index_to_delete(tmp_min) == 0)
				return (0);
			if (delete_index(tmp_min) == 0)
				return (0);
			tmp_min++;
		}
		return (1);
	}
	return (0);
}
