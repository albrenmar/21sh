/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 01:23:51 by mjose             #+#    #+#             */
/*   Updated: 2019/03/25 05:56:56 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		is_simple_expand(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && !ft_iswhitespace(value[i + 1])
				&& value[i + 1] != '{')
			return (1);
		else if (value[i] == '$' && value[i + 1]
				&& !ft_iswhitespace(value[i + 1]) && value[i + 1] == '{')
		{
			while (value[i] && value[i] != ':' && value[i] != '#'
				&& value[i] != '%')
			{
				if (value[i] == '}')
					return (1);
				i++;
			}
		}
		else if (value[i] == '$' && value[i + 1] && value[i + 1] == '{'
				&& value[i + 2] && ft_iswhitespace(value[i + 2]))
			return (-1);
		i++;
	}
	return (0);
}

void	delete_letter_expand(t_expand **letter)
{
	t_expand	*prev;
	t_expand	*next;

	prev = (*letter)->prev;
	next = (*letter)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
//	free(*letter);
	if (next)
		*letter = next;
	else
		*letter = NULL;
}

void	delete_list_expand(t_expand **letter)
{
	t_expand	*next;

	next = NULL;
	while (*letter && (*letter)->next)
	{
		if ((*letter)->next)
			next = (*letter)->next;
		delete_letter_expand(letter);
		if (next)
			*letter = next;
		else
			*letter = NULL;
	}
	*letter = NULL;
}

void	update_envp(void)
{
	int		i;

	i = 0;
	while (g_tracking.mysh->tab_env[i])
		ft_strdel(&g_tracking.mysh->tab_env[i++]);
	if (g_tracking.mysh->tab_env)
		free(g_tracking.mysh->tab_env);
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
}

void	update_list_expand(t_expand **letter, char **str)
{
	t_expand	*new_letter;
	char		*cop_str;

	cop_str = ft_strdup(*str);
	delete_list_expand(letter);
//	expand_lstdel(*letter);
	*letter = NULL;
	new_letter = new_expand(ft_strlen(*str));
	*letter = new_letter;
	if (cop_str[0] == '0')
	{
		cop_str[0] = '1';
		create_list_expand(*letter, cop_str);
	}
	else
		create_list_expand(*letter, *str);
	ft_strdel(&cop_str);
	update_envp();
}
