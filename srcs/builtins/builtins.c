/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/05 03:33:10 by abguimba         ###   ########.fr       */
=======
/*   Updated: 2019/03/01 07:41:56 by abguimba         ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			is_builtin(void)
{
<<<<<<< HEAD
	if (ft_builtin_search("jobs") || ft_builtin_search("fg")
		|| ft_builtin_search("bg") || ft_builtin_search("exit")
		|| ft_builtin_search("set") || ft_builtin_search("echo")
		|| ft_builtin_search("hash") || ft_builtin_search("test")
		|| ft_builtin_search("cd"))
=======
	if (ft_builtin_search("jobs") || ft_builtin_search("fg") ||
		ft_builtin_search("bg") || ft_builtin_search("exit") ||
		ft_builtin_search("set") || ft_builtin_search("hash") || 
		ft_builtin_search("test"))
>>>>>>> alsomvil
		return (1);
	return (0);
}

int			is_builtin_alone(void)
{
	t_jobs	*tmp;
	int		i;

	i = 0;
	tmp = g_tracking.jobs;
	if (!(is_builtin()))
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->name[i] != '\0')
	{
		if (tmp->name[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

int			ft_builtin_search(char *builtin)
{
	char	*tmp;
	int		i;

	tmp = g_tracking.g_tab_exec[0];
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

<<<<<<< HEAD
int			builtin_exec()
=======
int			builtin_exec(t_last *arglist)
>>>>>>> alsomvil
{
	if (ft_builtin_search("jobs"))
		return (jobs_builtin());
	else if (ft_builtin_search("fg"))
		return (fg_builtin());
	else if (ft_builtin_search("bg"))
		return (bg_builtin());
	else if (ft_builtin_search("set"))
		return (show_setenv());
<<<<<<< HEAD
	else if (ft_builtin_search("echo"))
		return (check_and_exec_echo());
=======
>>>>>>> alsomvil
	else if (ft_builtin_search("exit"))
		return (ft_exit());
	else if (ft_builtin_search("hash"))
		return (ft_hash());
	else if (ft_builtin_search("test"))
<<<<<<< HEAD
		return (main_test());
	 else if (ft_builtin_search("cd"))
		return (ft_cd());
=======
		return (main_test(arglist));
>>>>>>> alsomvil
	return (0);
}
