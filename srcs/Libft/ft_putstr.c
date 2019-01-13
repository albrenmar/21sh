/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:58:35 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/13 21:03:59 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	int	i;

	if (*s)
	{
		i = ft_strlen(s);
		write(1, s, i);
	}
}

void	ft_putstr_nocar(char const *s)
{
	int	i;

	if (*s)
	{
		i = 0;
		while (s[i])
		{
			if (s[i] != '\r')
				ft_putchar(s[i]);
			i++;
		}
	}
}
