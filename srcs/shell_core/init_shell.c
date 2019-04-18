/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 01:33:09 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	reset_all(void)
{
	reset_tmpenv();
	reset_resetenv();
	cursor_reset();
}

void	init_global(void)
{
	g_tracking.mysh->resetenv = NULL;
	g_tracking.mysh->envsave = NULL;
	g_tracking.mysh->tmpenv = NULL;
	g_tracking.mysh->expand_error = 0;
	g_tracking.mysh->err_expend = 0;
	g_tracking.cmdindex = -1;
	g_tracking.builtin = 0;
	g_tracking.jobs = NULL;
	g_tracking.lastreturn = 0;
	g_tracking.expandreturn = 0;
	g_tracking.mysh->hist = NULL;
	g_tracking.mysh->alias_lst = NULL;
	g_tracking.g_tab_exec = NULL;
	g_tracking.prompt = NULL;
	g_tracking.cwd = NULL;
	g_tracking.user = NULL;
	g_tracking.cwd = NULL;
}

void	init_shell(char **environ, char **argv)
{
	t_shell		*mysh;
	int			i;

	i = 0;
	if (!(mysh = ft_malloc(sizeof(t_shell))))
	{
		ft_putendl("Failed to allocate memory");
		ft_exit2(EXIT_FAILURE);
	}
	while (i++ < 27)
		g_tracking.hashtable[i] = NULL;
	g_tracking.cwd = NULL;
	g_tracking.mysh = mysh;
	init_global();
	init_alias();
	g_tracking.mysh->env = ft_env_to_lst(environ);
	g_tracking.mysh->hist = NULL;
	add_missing_string();
	if (write(0, argv[0], 0) != -1)
		hist_file_to_lst();
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->set_env = NULL;
	g_tracking.mysh->expand_error = 0;
	g_tracking.quotes = 0;
}
