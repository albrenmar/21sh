/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 06:38:10 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 01:02:11 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			is_space_ac(char *tmp, int i)
{
	char	c;

	c = '\0';
	if (i < 0)
		return (1);
	c = tmp[i];
	if (i > 0)
		if (tmp[i - 1] == '\\')
			return (0);
	if (c == ' ' || c == '\t' || c == ';' || c == '\0')
		return (1);
	if (c == '/')
		return (2);
	else
		return (0);
}

int			back_up_str(char *tmp, int i)
{
	if (tmp[i] == '\0')
		i--;
	while (tmp[i] && i != 0)
	{
		while (tmp[i] != '\0' && is_space_ac(tmp, i) != 1 && i != 0)
			i--;
		break ;
	}
	i++;
	return (i);
}

int			start_word(void)
{
	char	*tmp;
	int		i;
	int		a;

	i = utf_goto(g_tracking.str, g_tracking.pos->abs);
	tmp = g_tracking.str;
	i--;
	a = 0;
	if (tmp != NULL && i > 0)
		a = back_up_str(tmp, i);
	return (a);
}

int			edge_case(void)
{
	int		k;
	char	*tmp;

	if (!g_tracking.str)
		return (1);
	tmp = g_tracking.str;
	k = utf_goto(g_tracking.str, g_tracking.pos->abs);
	if (is_space_ac(tmp, k) == 1)
	{
		if (is_space_ac(tmp, (k - 1)) == 1)
		{
			g_tracking.aut->word = NULL;
			return (1);
		}
		if (is_space_ac(tmp, (k - 1)) == 2)
		{
			if (is_space_ac(tmp, (k - 2) == 1))
			{
				exit(0);
				g_tracking.aut->word = ft_strdup("/");
				return (1);
			}
		}
	}
	return (0);
}

void		assign_word(void)
{
	int		len;
	int		i;
	int		a;

	len = 0;
	i = 0;
	a = 0;
	g_tracking.aut->word = NULL;
	if (edge_case() == 1)
		return ;
	i = end_word(0);
	a = start_word();
	len = i - a;
	g_tracking.aut->word = ft_strsub(g_tracking.str, a, len, 0);
}
