/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/23 07:19:10 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_jobs		*new_job_helper(t_jobs *tmp)
{
	int		i;
	t_jobs	*hold;

	i = 2;
	hold = NULL;
	while (tmp->next)
	{
		hold = tmp;
		tmp = tmp->next;
		i++;
	}
	hold = tmp;
	if (!(tmp->next = malloc(sizeof(t_jobs))))
		return (NULL);
	tmp = tmp->next;
	if (hold->next && hold == tmp)
		tmp->prev = hold->next;
	else
		tmp->prev = hold;
	tmp->place = hold->place + 1;
	return (tmp);
}

char		*job_name_maker_helper(int spaces, int len, t_last *head)
{
	char	*new;

	if (!(new = malloc(sizeof(char) * (len + spaces + 1))))
		return (NULL);
	len = 0;
	while (head && ft_strcmp(head->name, "&"))
	{
		spaces = 0;
		while (head->name[spaces] != '\0')
		{
			new[len] = head->name[spaces];
			len++;
			spaces++;
		}
		if (head->next)
			new[len++] = ' ';
		head = head->next;
	}
	new[len] = '\0';
	return (new);
}
