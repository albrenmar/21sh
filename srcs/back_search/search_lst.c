/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 00:28:43 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 04:13:27 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/02/24 02:52:26 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

<<<<<<< HEAD
int				ft_strstr_ptr(const char *haystack, const char *needle)
=======
int 	ft_strstr_ptr(const char *haystack, const char *needle)
>>>>>>> alsomvil
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return (-1);
	while (haystack[i])
	{
		while (needle[j] == haystack[i])
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return ((i - ft_strlen(needle)));
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (-1);
}

<<<<<<< HEAD
char			*get_hist_ptr(char *needle)
{
	t_hist		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	tmp = get_hist_nbr(g_tracking.histindex - 1);
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if ((i = ft_strstr_ptr(tmp->line, needle) != -1))
		{
			return (tmp->line);
		}
		tmp = tmp->previous;
		if (g_tracking.histindex > 1)
			g_tracking.histindex--;
	}
	return (NULL);
}
=======
char         *get_hist_ptr(char *needle)
{
    t_hist      *tmp;
    int         i;

    tmp = NULL;
    i = 0;
    tmp = get_hist_nbr(g_tracking.histindex - 1);
    if (!tmp)
        return (NULL);
    while (tmp)
    {
        if ((i = ft_strstr_ptr(tmp->line, needle) != -1))
        {
            return(tmp->line);
        }
        tmp = tmp->previous;
        if (g_tracking.histindex > 1)
		    g_tracking.histindex--;
    }
    return (NULL);
}
>>>>>>> alsomvil
