/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/18 18:23:16 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			is_builtin(int mode)
{
	if (mode == 1)
	{
		if (ft_builtin_search("jobs") || ft_builtin_search("fg") ||
		ft_builtin_search("bg") || ft_builtin_search("exit"))
			return (1);
	}
	else if (mode == 2)
	{
		if (ft_builtin_search("fg") || ft_builtin_search("exit") ||
		ft_builtin_search("bg"))
			return (1);
	}
	return (0);
}

int			ft_exit(int mode)
{
	if (!g_tracking.jobs->next)
	{
		if (mode == 1)
		{
			ft_putendl("Exit");
			exit(0);
		}
		return (0);
	}
	else
	{
		if (mode == 1)
			ft_putendl("There are still jobs running you idiot!");
	}
	return (1);
}

int			ft_builtin_search(char *builtin)
{
	char	*tmp;
	int		i;

	tmp = ORDER->command[0];
	i = 0;
	while (tmp[i] && (tmp[i] == '\'' || tmp[i] == '\"'))
		i++;
	while (*builtin && *builtin == tmp[i])
	{
		builtin++;
		i++;
	}
	if (*builtin == '\0' && tmp[i] == '\0')
		return (1);
	return (0);
}

int			builtin_exec(int mode)
{
	if (mode != 1 && ft_builtin_search("jobs"))
		return (jobs_builtin());
	else if (ft_builtin_search("fg"))
		return (fg_builtin(mode));
	else if (ft_builtin_search("bg"))
		return (bg_builtin(mode));
	else if (ft_builtin_search("exit"))
		return (ft_exit(mode));
	return (0);
}