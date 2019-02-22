/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/18 20:14:47 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	// t_tab	st_tab;
	t_env	*st_env;
	t_last	*cmd;
	char	*prompt;
	t_tab_arg	*tab_arg;

    tab_arg = NULL;
	line = NULL;
	argc = 0;
	argv = NULL;
	st_env = NULL;
	if (env[0])
		env_format(env, &st_env);
	//	set_env(&st_env, env);
	cursorinit();
	prompt = ft_strdup("Fake minishell > ");
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = ft_strlen(prompt);
	// ft_siginit();
	init_shell(env);
	get_term();
	// init_jobs();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
	while (get_key() > 0)
	{
		// jobs_notifications();
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.swi = 0;
		ft_putchar('\n');
		hist_lst_add_next(g_tracking.mysh->hist, line);
		// if (!ft_strcmp(line, "exit") && ft_strlen(line) == 4)
		// 	ft_exit();
		if (line && (cmd = ft_parseur(line)))
			cmd_manager(cmd, tab_arg);
		jobs_notifications();
		jobs_update_current();
		// jobs_debug();
		//ft_build_test(line);
		free(line);
		line = NULL;
	}
	return (0);
}
