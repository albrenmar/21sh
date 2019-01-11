/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/09 23:27:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_type(void)
{
	char	*check;

	check = g_tracking.aut->word;
	if(check[0] == '/')
		return(1);
	if(check[1] != '\0')
	{
		if (check[0] == '.' && check[1] == '/')
			return(1);
		if (check[2] != '\0')
			if (check[0] == '.' && check[1] == '.' && check[2] == '/')
				return(1);
	}
	if (check[0] == '$')
		return (2);
	else
		return (0);
}

void	rm_slash(void)
{
	t_lstcontainer		*tmp;
	t_list				*buf;
	int					i;

	i = 0;
	while (g_tracking.aut->word[i])
		i++;
	if (i > 0)
	{
		i--;
		if (g_tracking.aut->word[i] == '/')
			g_tracking.aut->word = NULL;
	}
	if (g_tracking.aut->word)
	{
		if (g_tracking.aut->word[0] == '/')
		{
			tmp = ft_strsplitlst(g_tracking.str, '/');
			if (tmp != NULL)
			{
				buf = ft_lstgetlast(tmp->firstelement);
				g_tracking.aut->word = ft_strdup(buf->content);
				ft_freesplitlist(tmp);
			}
		}
	}
}

int		sanitize_path(void)
{
	t_lstcontainer	*tmp;
	t_list			*buf;
	char			*path;
	int				i;

	tmp = ft_strsplitlst(g_tracking.aut->word, '/');
	i = lstcontainer_size(tmp);
	if (i > 1)
	{
		path = ft_strnew(0);
		buf = tmp->firstelement;
		while (buf->next != NULL)
		{
			path = ft_strjoinfree("/", path, 2);
			path = ft_strjoinfree(path, buf->content, 1);
			path = ft_strjoinfree(path, "/", 1);
			buf = buf->next;
		}
		ft_freesplitlist(tmp);
		free(g_tracking.aut->path);
		g_tracking.aut->path = path;
		return (1);
	}
	return (0);
}

void	assign_type(void)
{
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->word != NULL)
	{
		g_tracking.aut->type = check_type();
		if (g_tracking.aut->type == 1)
		{
			g_tracking.aut->path = ft_strdup(g_tracking.aut->word);
			sanitize_path();
			rm_slash();
		}
	}
}