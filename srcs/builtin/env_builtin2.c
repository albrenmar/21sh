/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:26:42 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:30:14 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_env_if_arg(t_core *core, int index)
{
	char		*cmd;
	char		**env;
	pid_t		pid;
	char		**arg;

	if ((cmd = test_command(core, index)))
	{
		if (!(arg = set_new_arg(core, index)))
			return ;
		if (!(env = ft_env_to_tab(core)))
			return ;
		pid = fork();
		if (pid > 0)
			wait(0);
		if (pid == 0)
			ft_execve(cmd, arg, env, core);
		free(cmd);
		ft_free_tab(arg);
		ft_free_tab(env);
		cmd = NULL;
	}
}

static void		ft_env_if_arg(t_core *core)
{
	int			i;
	int			j;

	i = 1;
	j = 1;
	while (core->arg[i])
	{
		if (ft_strcmp(core->arg[i], "-i") == 0)
		{
			ft_putendl_fd("env -i Command not found", 2);
			return ;
		}
		if (ft_strrchr(core->arg[i], '=') != NULL)
			j++;
		i++;
	}
	if (core->arg[j])
		exec_env_if_arg(core, j);
	else
		ft_putendl_fd("usage: env NAME=VALUE cmd", 2);
}

static void		ft_env_without_arg(t_core *core)
{
	t_env		*lst;

	lst = core->env;
	while (lst)
	{
		ft_putendl(lst->env);
		lst = lst->next;
	}
}

void			ft_print_env(t_core *core)
{
	if (core->arg[1])
		ft_env_if_arg(core);
	else if (ft_count_list(core->env) > 0)
		ft_env_without_arg(core);
}

bool			ft_envexist(const char *search, t_env *env)
{
	if (!env || !search)
		return (ERROR);
	while (env)
	{
		if (ft_strcmp(env->name, search) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}
