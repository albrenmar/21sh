/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/29 03:22:42 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"
#include "expansions.h"

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
	set_env(&st_env, env);
	cursorinit();
	prompt = ft_strdup("Fake minishell > ");
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = ft_strlen(prompt);
	ft_siginit();
	get_term();
	while (get_key() > 0)
	{
		/* A REMPLACER PAR FONCTIONS BSICHE */
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		expand_transformer(line, &st_env);
		g_tracking.swi = 0;
		ft_putchar('\n');
		/* A REMPLACER PAR FONCTIONS BSICHE */
		cmd = ft_analize(line);
		apply_cmd(&st_tab, &st_env, cmd, env);
		free(line);
		line = NULL;
	}
	forfree(st_env.env);
	return (0);
}