/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:26:54 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/18 12:32:23 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*test_command(t_core *core, int index)
{
	int			i;
	char		*tmp;
	char		*to_free;

	i = -1;
	if (!core->path && (tmp = ft_strdup(core->arg[index])))
	{
		if (access(tmp, F_OK) != -1)
			return (tmp);
		free(tmp);
	}
	while (core->path && core->path[++i])
	{
		if (!ft_strchr(core->arg[index], '/'))
		{
			to_free = ft_strjoin(core->path[i], "/");
			tmp = ft_strjoinfree(to_free, core->arg[index], 1);
		}
		else
			tmp = ft_strdup(core->arg[index]);
		if (access(tmp, F_OK) != -1)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

static int		ft_arg_is_valid(t_core *core)
{
	if (!core->arg[1])
		return (5);
	else if (ft_strindexchr(core->arg[1], '=') == 0)
		return (2);
	else if (ft_strcountoccur(core->arg[1], '=') > 1)
		return (3);
	else
		return (TRUE);
}

void			ft_check_setenv(t_core *core)
{
	char		**tmp;

	if (ft_sstrlen(core->arg) == 2 && ft_arg_is_valid(core) == 1)
	{
		tmp = ft_strsplit(core->arg[1], '=');
		if (tmp[1])
			ft_setenv(core, tmp[0], tmp[1]);
		else
			ft_setenv(core, tmp[0], ft_strdup(""));
		free(tmp);
	}
	else
		ft_error(ft_arg_is_valid(core));
}

void			exec_cmd(t_core *core, char *tmp)
{
	char		**env;
	pid_t		pid;
	t_stat		st;

	if (!(env = ft_env_to_tab(core)))
		return ;
	lstat(tmp, &st);
	if (S_ISDIR(st.st_mode) || !(st.st_mode & S_IXUSR))
		ft_putendl_fd("Not a binary", 2);
	else
	{
		pid = fork();
		(pid > 0) ? wait(0) : 0;
		if (pid == 0)
		{
			if (access(tmp, X_OK) != -1)
				((execve(tmp, core->arg, env)) == -1) ? exit(1) : 1;
			else
				perm_denied(core);
		}
	}
	free(tmp);
	ft_free_tab(env);
	tmp = NULL;
}

void			ft_run_command(t_core *core)
{
	char		*tmp;

	if (ft_strcmp(core->arg[0], "env") == 0)
		ft_print_env(core);
	else if (ft_strcmp(core->arg[0], "setenv") == 0)
		ft_check_setenv(core);
	else if (ft_strcmp(core->arg[0], "unsetenv") == 0)
		(core->arg[1]) ? core->env = ft_unsetenv(core, core->arg[1]) : 0;
	else if (ft_strcmp(core->arg[0], "cd") == 0)
		ft_cd(core);
	else if (ft_strcmp(core->arg[0], "echo") == 0)
		echo_builtin(core);
	else if (ft_strcmp(core->arg[0], "which") == 0)
		which_builtin(core);
	else if (ft_strcmp(core->arg[0], "exit") == 0)
		exit_builtin(core);
	// history builtin
	else if (ft_strcmp(core->arg[0], "history") == 0)
		history_builtin(core);
	else if ((tmp = test_command(core, 0)) != NULL)
		exec_cmd(core, tmp);
	else
	{
		ft_putstr_fd(NOT_FOUND, 2);
		ft_putendl_fd(core->arg[0], 2);
	}
}
