/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_alias_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/25 23:50:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			get_last_char_helper(char *str, char *memory, int i, int j)
{
	while (i > 0 && j > 0 && str[i] == memory[j])
	{
		i--;
		j--;
	}
	return (i + 1);
}

int			get_last_char_alias(char *str, char *memory, int nbsave, int j)
{
	int		i;
	int		saver;

	saver = nbsave;
	i = 0;
	while (nbsave > 0)
	{
		while (is_spaces(str, i, 1))
			i++;
		while (str[i] && !is_spaces(str, i, 2))
			i++;
		nbsave--;
	}
	while (saver > 0)
	{
		while (is_spaces(memory, j, 1))
			j++;
		while (memory[j] && !is_spaces(memory, j, 2))
			j++;
		saver--;
	}
	return (get_last_char_helper(str, memory, i - 1, j - 1));
}
