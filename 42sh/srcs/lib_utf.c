/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/18 16:54:17 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			utf_byte(char c)
{
	if ((c & 0xC0) != 0x80)
		return (0);
	return (1);
}

int			get_nb_char(unsigned char c)
{
	if (c >= 0xF0 && c <= 0xF4)
		return (3);
	if (c >= 0xE0 && c <= 0xEF)
		return (2);
	if (c >= 0xC0 && c <= 0xDF)
		return (1);
	else
		return (0);
}

int			utf_goto(char *str, int j)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (a != j)
	{
		i += get_nb_char(str[i]);
		i++;
		a++;
	}
	return (i);
}

int			utf_strlen(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if ((str[i] & 0xC0) != 0x80)
			a++;
		i++;
	}
	return (a);
}