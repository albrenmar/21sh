/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:59:49 by bsiche            #+#    #+#             */
/*   Updated: 2018/05/21 23:05:38 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if ((str = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	str[i++] = '\0';
	return (str);
}

char	*ft_strdupfree(char *s)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if ((str = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	str[i++] = '\0';
	free(s);
	return (str);
}
