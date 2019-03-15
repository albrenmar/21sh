/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/15 01:12:39 by bsiche           ###   ########.fr       */
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

	line = NULL;
	if (argc > 2)
		argc_error();
	argc = 0;
	if (ft_strcmp(argv[1], "-u") == 0)
		g_tracking.unlink = 1;
	else
		g_tracking.unlink = 0;	
	//	set_env(&st_env, env);
	// ft_siginit();
	cursorinit();
	init_shell(env);
	get_term();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.cmd = NULL;
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		if ((line = shebang_parse_switch(line)) != NULL)
		{
			if ((ft_strlen(line) > 0) && spaces_line_check(line) && (cmd = ft_parseur(line)))
			{
				if (g_tracking.interactive == 1)
					ft_putchar('\n');
				hist_lst_add_next(g_tracking.mysh->hist, line);
				convert_list(cmd);
				ft_ast(cmd);
			}
		}
		jobs_notifications();
		jobs_update_current();
		free(line);
		line = NULL;
	}
	return (0);
}