/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:22 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/10 14:45:47 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_core	*ft_init(int argc, char **argv, char **env)
{
	t_core		*core;
	int			i;
	char		**split;

	i = 0;
	core = create_core_struct();
	core->argv = argv;
	core->argc = argc;
	core->arg = NULL;
	core->env = create_lst();
	while (env[i])
	{
		if (!(split = ft_strsplit(env[i], '=')))
			return (NULL);
		if (!(core->env = pushback(core->env, split[0], split[1], env[i])))
			return (NULL);
		i++;
		ft_free_tab(split);
	}
	return (core);
}

static char		**ft_parse_path(t_core *core)
{
	char		**parse;
	char		*path;

	if (ft_envexist("PATH", core->env))
	{
		path = ft_getenv("PATH", core->env);
		parse = ft_strsplit(path, ':');
		return (parse);
	}
	else
		return (NULL);
}

char			**ft_setenv_if_empty(char **env)
{
	if (ft_sstrlen(env) == 0)
	{
		env[0] = ft_strjoinfree("PWD=", getcwd(NULL, 4096), 2);
		env[1] = 0;
	}
	return (env);
}

void			minishell(int argc, char **argv, char **env)
{
	t_core		*core;

	signal(SIGINT, signal_handler);
	ft_check_arg(argv);
	env = ft_setenv_if_empty(env);
	core = ft_init(argc, argv, env);
	// Without that crash one on two
	core->hist = NULL;
	ft_display_prompt(0);
	while ((core->ret = get_next_line(0, &core->line)))
	{
		g_signal_c = 0;
		core->path = ft_parse_path(core);
		core->arg = ft_split_whitespaces(core->line);
		// Put history setup
		history_setup(core);
		if (core->arg[0] != '\0' && ft_check_args(core->line) != ERROR)
			ft_run_command(core);
		free(core->line);
		ft_free_tab(core->path);
		ft_free_tab(core->arg);
		if (!g_signal_c)
			ft_display_prompt(0);
	}
	ft_free_list(core->env);
	free(core->line);
	free(core);
}
