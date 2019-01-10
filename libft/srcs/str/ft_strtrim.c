/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:23:24 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:23:24 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_whitespaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char		*result;
	size_t		i;
	size_t		k;
	size_t		len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (is_whitespaces(s[i]) && s[len])
		i++;
	while (is_whitespaces(s[len]) && s[i])
		len--;
	k = (len - i) + 1;
	result = ft_strsub(s, i, k);
	return (result);
}
