/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:22:12 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:22:13 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	str = NULL;
	if (!(str = (char *)(malloc(sizeof(char) * (len + ft_strlen(s2) + 1)))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}
