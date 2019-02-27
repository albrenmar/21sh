/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/15 04:40:52 by mjose            ###   ########.fr       */
=======
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/26 06:21:19 by abguimba         ###   ########.fr       */
>>>>>>> mjose.merge
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"
<<<<<<< HEAD
#include "expansions.h"
=======

>>>>>>> mjose.merge

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	t_last	*cmd;
	char	*prompt;
<<<<<<< HEAD
	t_tab_arg	*tab_arg;
=======
>>>>>>> mjose.merge

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
<<<<<<< HEAD
=======
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
>>>>>>> mjose.merge
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.swi = 0;
		ft_putchar('\n');
		hist_lst_add_next(g_tracking.mysh->hist, line);
<<<<<<< HEAD
		if (!ft_strcmp(line, "exit"))
		{
			printf("%s\n", "exit temporaire");
			exit(0);
		}
		else if (line && (cmd = ft_parseur(line)))
		{
			expand_transformer(cmd);
			tab_arg = convert_to_list_tab(cmd);
			ft_ast(tab_arg);
		}
		//ft_build_test(line);
=======
		if (line && (cmd = ft_parseur(line)))
		{
			convert_list(cmd);
			ft_ast(cmd);
		}
		jobs_notifications();
		jobs_update_current();
>>>>>>> mjose.merge
		free(line);
		line = NULL;
	}
	return (0);
}
