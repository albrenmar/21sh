/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:21:02 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:21:03 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count_words(char *str)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		{
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
					&& str[i] != '\0')
				i++;
			k++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (k);
}

static int		ft_len_words(char *str, int i)
{
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static char		**ft_tab_cpy(char **dest, char *str, int i, int j)
{
	int			k;

	dest = malloc((ft_count_words(str) + 1) * sizeof(char*));
	while (str[i])
	{
		k = 0;
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
			i++;
		if (str[i] != '\0')
		{
			dest[j] = malloc((ft_len_words(str, i) + 1) * sizeof(char));
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
					&& str[i] != '\0')
			{
				dest[j][k] = str[i];
				i++;
				k++;
			}
			dest[j][k] = '\0';
			j++;
		}
	}
	dest[j] = 0;
	return (dest);
}

char			**ft_split_whitespaces(char *str)
{
	int			i;
	int			j;
	char		**dest;

	i = 0;
	j = 0;
	dest = 0;
	dest = ft_tab_cpy(dest, str, i, j);
	return (dest);
}
