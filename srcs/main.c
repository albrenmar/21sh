/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/07 02:29:18 by abguimba         ###   ########.fr       */
=======
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/07 22:19:53 by alsomvil         ###   ########.fr       */
>>>>>>> alsomvil
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
<<<<<<< HEAD

	line = NULL;
	if (argc > 1)
		argc_error();
	argc = 0;
	argv = NULL;
	//	set_env(&st_env, env);
	// ft_siginit();
	cursorinit();
=======
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
>>>>>>> alsomvil
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
		ft_putchar('\n');
<<<<<<< HEAD
		if ((ft_strlen(line) > 0) && spaces_line_check(line) && (cmd = ft_parseur(line)))
		{
			hist_lst_add_next(g_tracking.mysh->hist, line);
			convert_list(cmd);
			ft_ast(cmd);
		}
		jobs_notifications();
		jobs_update_current();
		free(line);
=======
		hist_lst_add_next(g_tracking.mysh->hist, line);
		if (line && (cmd = ft_parseur(line)))
		{
			convert_list(cmd);
			ft_ast(cmd);
		}
		printf("test\n");
		jobs_notifications();
		jobs_update_current();
		//free(line);
>>>>>>> alsomvil
		line = NULL;
	}
	return (0);
}
