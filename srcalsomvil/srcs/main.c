/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 18:16:57 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	pid_t	father;
	t_cmd	*cmd;

	line = NULL;
	set_env(&st_env, env);
	while (42)
	{
		ft_dprintf(2, "%s", "%> ");
		/* A REMPLACER PAR FONCTIONS BSICHE */
		if (get_next_line(0, &line) < 1)
			exit(0);
		/* A REMPLACER PAR FONCTIONS BSICHE */
		cmd = ft_analize(line);
		apply_cmd(&st_tab, &st_env, cmd, env);
		free(line);
	}
	forfree(st_env.env);
	return (0);
}
