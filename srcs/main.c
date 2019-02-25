/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/23 12:25:58 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"


int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	t_last	*cmd;
	char	*prompt;

	line = NULL;
	argc = 0;
	argv = NULL;
	//	set_env(&st_env, env);
	cursorinit();
	prompt = ft_strdup("Fake minishell > ");
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = ft_strlen(prompt);
	ft_siginit();
	init_shell(env);
	get_term();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.swi = 0;
		ft_putchar('\n');
		hist_lst_add_next(g_tracking.mysh->hist, line);
		// if (!ft_strcmp(line, "exit"))
		// {
		// 	printf("%s\n", "exit temporaire");
		// 	exit(0);
		// }
		if (line && (cmd = ft_parseur(line)))
		{
			convert_list(cmd);
			ft_ast(cmd);
		}
		jobs_notifications();
		jobs_update_current();
		//ft_build_test(line);
		free(line);
		line = NULL;
	}
	return (0);
}
