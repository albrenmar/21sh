/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:22:16 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:22:16 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoinfree(char *s1, char *s2, size_t tofree)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	if (!(new_str = ft_strjoin(s1, s2)))
		return (NULL);
	if (tofree == 1)
		free(s1);
	else if (tofree == 2)
		free(s2);
	else if (tofree == 3)
	{
		free(s1);
		free(s2);
	}
	return (new_str);
}
