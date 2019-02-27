/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/01/23 00:27:08 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/02/24 03:18:44 by bsiche           ###   ########.fr       */
>>>>>>> mjose.merge
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_type(void)
{
	char	*check;

	check = g_tracking.aut->word;
	if (check[0] == '/')
		return (1);
	if (check[1] != '\0')
	{
		if (check[0] == '.' && check[1] == '/')
			return (1);
		if (check[0] == '$' && check[1] == '{')
			return (2);
		if (check[2] != '\0')
			if (check[0] == '.' && check[1] == '.' && check[2] == '/')
				return (1);
		if (check[ft_strlen(check) - 1] == '/')
			return (1);
	}
	return (0);
}

void	escape_path(void)
{
	t_lstcontainer	*tmp;
	t_list			*buf;
	char			*string;

	tmp = NULL;
	tmp = ft_strsplitlst(g_tracking.aut->to_add, ' ');
	if (lstcontainer_size(tmp) > 1)
	{
		string = ft_strnew(0);
		buf = tmp->firstelement;
		while (buf)
		{
			string = ft_strjoinfree(string, buf->content, 1);
			if (buf->next)
				string = ft_strjoinfree(string, "\\ ", 1);
			buf = buf->next;
		}
		free(g_tracking.aut->to_add);
		g_tracking.aut->to_add = string;
	}
	ft_freesplitlist(tmp);
	g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, "/", 1);
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
		tmp = ft_strsplitlst(g_tracking.str, '/');
		if (tmp != NULL)
		{
			buf = ft_lstgetlast(tmp->firstelement);
			g_tracking.aut->word = ft_strdup(buf->content);
			ft_freesplitlist(tmp);
		}
	}
}

int		sanitize_path(void)
{
	int		i;
	int		a;
	char	*path;

	i = ft_strlen(g_tracking.aut->word);
	a = 0;
	while (g_tracking.aut->word[i] != '/' && i > 0)
		i--;
	path = ft_strnew(i);
	while (i > a)
	{
		path[a] = g_tracking.aut->word[a];
		a++;
	}
	path = ft_strjoinfree(path, "/", 1);
	g_tracking.aut->path = path;
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
		if (g_tracking.aut->type == 2)
		{
			g_tracking.aut->word = ft_strsub(g_tracking.aut->word, 2, ft_strlen(g_tracking.aut->word) , 1);
			complete_usr_var();
		}
	}
}