/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtables.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/25 17:17:08 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

char		**hashed_command(char **tab_exec)
{
	char	**newtab;
	int		index;
	t_hash	*tmp;

	if (strchr(g_tracking.g_tab_exec[0], '/'))
		return (NULL);
	index = hash_maker(tab_exec[0]);
	newtab = tab_dup(tab_exec);
	ft_strdel(&newtab[0]);
	tmp = g_tracking.hashtable[index];
	while (tmp)
	{
		if (!(ft_strcmp(tmp->binary, tab_exec[0])))
		{
			newtab[0] = ft_strdup(tmp->path);
			free_tab(tab_exec);
			return (newtab);
		}
		tmp = tmp->nextbinary;
	}
	free_tab(tab_exec);
	return (NULL);
}

t_hash		*new_binary_hash(char *binary, char *path, int hits)
{
	t_hash	*new;

	if (!(new = malloc(sizeof(t_hash))))
		return (NULL);
	new->binary = ft_strdup(binary);
	new->path = ft_strdup(path);
	new->totalhits = hits;
	new->nextbinary = NULL;
	return (new);
}

void		insert_to_hashtable(int key, char *binary, char *path)
{
	t_hash	*tmp;

	tmp = g_tracking.hashtable[key];
	if (tmp)
	{
		while (ft_strcmp(binary, tmp->binary) && tmp->nextbinary)
			tmp = tmp->nextbinary;
		if (!(ft_strcmp(binary, tmp->binary)))
		{
			if (ft_strcmp(tmp->path, path))
			{
				ft_strdel(&tmp->path);
				tmp->path = ft_strdup(path);
			}
			tmp->totalhits += 1;
		}
		else
		{
			tmp->nextbinary = new_binary_hash(binary, path, 1);
		}
	}
	else
	{
		g_tracking.hashtable[key] = new_binary_hash(binary, path, 1);
	}
}

int			hash_maker(const char *binary)
{
	return (ft_tolower(binary[0]) - 'a');
}

void		hash_binary(void)
{
	int		hashedvalue;
	char	*binaryhold;

	if (strchr(g_tracking.g_tab_exec[0], '/'))
		return ;
	binaryhold = ft_strdup(g_tracking.g_tab_exec[0]);
	if (!(test_exist_fonction(g_tracking.g_tab_exec)))
		return ;
	hashedvalue = hash_maker(binaryhold);
	insert_to_hashtable(hashedvalue, binaryhold, g_tracking.g_tab_exec[0]);
}
