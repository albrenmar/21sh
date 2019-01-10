/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:23:20 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:23:20 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsubfree(char *s, unsigned int start, size_t len)
{
	char *str;

	str = ft_strsub(s, start, len);
	ft_bzero(s, ft_strlen(s));
	return (str);
}
