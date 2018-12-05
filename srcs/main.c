/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/05 15:47:17 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/sh42.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	pid_t	father;
	t_cmd	*cmd;
	char	*prompt;
	int		i;

	line = NULL;
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
		g_tracking.swi = 0;
		ft_putchar('\n');
		/* A REMPLACER PAR FONCTIONS BSICHE */
		cmd = ft_analize(line);
		apply_cmd(&st_tab, &st_env, cmd, env);
		free(line);
	}
	forfree(st_env.env);
	return (0);
}