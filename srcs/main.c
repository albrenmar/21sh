/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/28 05:15:02 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

t_last	*check_exp_error(t_last *cmd)
{
	t_last		*list_for_free;
	t_last		*begin;
	t_last		*prev;
	t_last		*next;

	begin = cmd;
	list_for_free = NULL;
	prev = NULL;
	next = NULL;
	while (cmd)
	{
		g_tracking.mysh->err_expend = 0;
		expand_transformer(&cmd->name);
		if (ft_strequ(cmd->name, " "))
		{
			ft_strdel(&cmd->name);
			prev = cmd->prev;
			next = cmd->next;
			if (cmd->next)
				cmd->next->prev = prev;
			if (cmd->prev)
				cmd->prev->next = next;
			ft_memdel((void **)&cmd);
			cmd = begin;
		}
		if (g_tracking.mysh->err_expend == 1)
		{
			while (cmd)
			{
				if ((ft_strlen(cmd->name) == 1) && cmd->name[0] == '|')
				{
					ft_putendl_fd("ERREUR EXPENSION", 2);
					cmd = cmd->next;
					cmd->prev->next = NULL;
					//FREE LE DEBUT DE LIST DEPUIS CMD->PREV
					cmd->prev = NULL;
					begin = cmd;
					//print_last(cmd);
					break ;
				}
				else if ((ft_strlen(cmd->name) == 2) && its_separator(cmd))
				{
					ft_putendl_fd("ERREUR EXPENSION", 2);
					//FREE LIST DEPUIS BEGIN
					return (NULL);
				}
				else if (cmd->next)
					cmd = cmd->next;
				else
				{
					ft_putendl_fd("ERREUR EXPENSION", 2);
					//FREE LIST DEPUIS BEGIN
					return (NULL);
				}
			}
			if (!cmd)
			{
				ft_putendl_fd("ERREUR EXPENSION", 2);
				//FREE LIST DEPUIS BEGIN
				return (NULL);
			}
		}
		else
			cmd = cmd->next;
	}
	return (begin);
}

void	set_up(char **argv, char **env)
{
	if (ft_strcmp(argv[1], "-u") == 0)
		g_tracking.unlink = 1;
	else
		g_tracking.unlink = 0;
	cursorinit();
	init_shell(env, argv);
	get_term();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
}

void	main_loop(char *line, char **argv)
{
	t_last	*cmd;

	if ((ft_strlen(line) > 0) && spaces_line_check(line)
	&& (cmd = ft_parseur(line)))
	{
		if (write(0, argv[0], 0) != -1)
			hist_lst_add_next(g_tracking.mysh->hist, line);
		convert_list(cmd);
		if (!error_lexer(cmd))
		{
			cmd = check_exp_error(cmd);
			if (cmd)
				ft_ast(cmd);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	line = NULL;
	if (argc > 2)
		argc_error();
	set_up(argv, env);
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.cmd = NULL;
		if (g_tracking.interactive == 1)
			ft_putchar_fd('\n', 0);
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		if ((line = shebang_parse_switch(line)) != NULL)
			main_loop(line, argv);
		jobs_notifications();
		jobs_update_current();
		free(line);
		line = NULL;
		g_tracking.sterminal = STDIN_FILENO;
		if (!(isatty(g_tracking.sterminal)))
			ft_exit(0, 0);
	}
	return (0);
}
