/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:03:06 by bsiche            #+#    #+#             */
/*   Updated: 2018/10/17 00:08:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_it(char const **s1, char const **s2, size_t free_level)
{
	if (free_level == 1)
		free((char *)(*s1));
	if (free_level == 2)
		free((char *)(*s2));
	if (free_level == 3)
	{
		free((char *)(*s1));
		free((char *)(*s2));
	}
}

char	*ft_strjoin(char const *s1, char const *s2, size_t free_level)
{
	size_t	i;
	char	*nstring;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((nstring = malloc(sizeof(char) * (size_s1 + size_s2 + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		nstring[i] = s1[i];
		i++;
	}
	while (i < size_s1 + size_s2)
	{
		nstring[i] = s2[i - size_s1];
		i++;
	}
	nstring[i] = '\0';
	free_it(&s1, &s2, free_level);
	return (nstring);
}

char	*ft_strjoinchar(char const *s1, char s2, size_t free_level)
{
	size_t	i;
	char	*nstring;
	size_t	size_s1;

	size_s1 = ft_strlen(s1);
	if (s1 == NULL || s2 == '\0')
		return (NULL);
	if ((nstring = malloc(sizeof(char) * (size_s1 + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		nstring[i] = s1[i];
		i++;
	}
	nstring[i] = s2;
	i++;
	nstring[i] = '\0';
	if (free_level == 1)
		free((char *)(s1));
	return (nstring);
}