/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/11 17:59:55 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_list(t_list *list_cmd)
{
	t_list	*templist;

	while (list_cmd->name)
	{
		templist = list_cmd->next;
		free(list_cmd->name);
		free(list_cmd);
		list_cmd = templist;
	}
	free(list_cmd);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	pid_t	father;
	t_list	*list_cmd;

	line = argv[1];
	set_env(&st_env, env);
	while (42)
	{
		ft_dprintf(2, "%s", "%> ");
		/* A REMPLACER PAR FONCTIONS BSICHE */
		if (get_next_line(0, &line) <= 0)
			exit(0);
		/* A REMPLACER PAR FONCTIONS BSICHE */
		list_cmd = ft_analize(line);
		free(line);
		apply_cmd(&st_tab, &st_env, list_cmd, env);
		free_list(list_cmd);
	}
	forfree(st_env.env);
	return (0);
}
