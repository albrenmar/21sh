/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 17:43:20 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void	print_last(t_last *list)
{
	t_last		*temp;

	temp = list;
	while (list)
	{
		printf("CMD = %s ET TYPE = %d\n", list->name, list->type);
		list = list->next;
	}
	list = temp;
}

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
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.swi = 0;
		ft_putchar('\n');
		hist_lst_add_next(g_tracking.mysh->hist, line);
		if (!ft_strcmp(line, "exit"))
		{
			printf("%s\n", "exit temporaire");
			exit(0);
		}
		else if (line && (cmd = ft_parseur(line)))
		{
			convert_list(cmd);
			ft_ast(cmd);
		}
		//ft_build_test(line);
		free(line);
		line = NULL;
	}
	return (0);
}
