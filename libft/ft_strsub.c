/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:57:22 by bsiche            #+#    #+#             */
/*   Updated: 2018/05/23 01:35:55 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, size_t start, size_t len, size_t freeit)
{
	size_t	i;
	char	*nstring;

	if (s == NULL)
		return (NULL);
	i = 0;
	nstring = (char *)malloc(sizeof(char) * (len + 1));
	if (nstring == NULL)
		return (NULL);
	while (i < len)
	{
		nstring[i] = s[start + i];
		i++;
	}
	nstring[i] = '\0';
	if (freeit == 1)
		free((char*)s);
	return (nstring);
}
