/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/11/16 14:45:47 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tab_path(t_tab *st_tab, char **env)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		str = ft_strndup(env[i], 5);
		if (ft_strcmp(str, "PATH=") == 0)
		{
			free(str);
			st_tab->tab_path = ft_strsplit(&env[i][5], ':');
			while (st_tab->tab_path[j])
			{
				str = ft_strjoin(st_tab->tab_path[j], "/");
				free(st_tab->tab_path[j]);
				st_tab->tab_path[j++] = str;
			}
			return ;
		}
		else
			free(str);
	}
	st_tab->tab_path = NULL;
}

void	recup_argument(t_tab *st_tab, t_env *st_env, char **line)
{
	if (*line && ft_strcmp(*line, "") != 0)
		st_tab->tab_word = ft_strsplit(*line, ' ');
	if (ft_strcmp(*line, "exit") == 0)
	{
		forfree(st_tab->tab_word);
		free(*line);
		exit(0);
	}
}

int		test_exist_fonction_two(t_tab *st_tab, t_env *st_env,
		pid_t father, char *next_str)
{
	int		i;

	i = 0;
	while (st_tab->tab_path && st_tab->tab_path[i])
	{
		next_str = ft_strjoin(st_tab->tab_path[i], st_tab->tab_word[0]);
		if (access(next_str, X_OK) == 0)
		{
			father = fork();
			if (father == 0)
				execve(next_str, st_tab->tab_word, st_env->env);
			free(next_str);
			wait(&father);
			forfree(st_tab->tab_path);
			return (1);
		}
		else
		{
			free(next_str);
			i++;
		}
	}
	return (0);
}

void	test_exist_fonction(t_tab *st_tab, char **line, t_env *st_env)
{
	char	*next_str;
	int		i;
	int		test_proc;
	pid_t	father;

	i = 0;
	if (access(st_tab->tab_word[0], X_OK) == 0)
	{
		father = fork();
		if (father == 0)
			execve(st_tab->tab_word[0], st_tab->tab_word, st_env->env);
		wait(&father);
		return ;
	}
	else
	{
		create_tab_path(st_tab, st_env->env);
		if (test_exist_fonction_two(st_tab, st_env, father, next_str) == 1)
			return ;
		forfree(st_tab->tab_path);
	}
	ft_dprintf(2, "%s%s\n", "minishell: command not found: ",
			st_tab->tab_word[0]);
	return ;
}

void	ft_create_tree(t_cmd *cmd)
{

}

void	apply_cmd(t_cmd *cmd)
{
	while (cmd->beginlist->name)
	{
		if (search_symbol(cmd->beginlist->name))
			ft_create_tree(cmd->beginlist->name);
		else
			apply_builtin(cmd->beginlist->name);
		free();
	}
}

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
		if (get_next_line(0, &line) < 1)
			exit(0);
		cmd = ft_analize(line);
		apply_cmd(cmd);
		/*while (cmd->beginlist->name)
		{
			if (ft_strcmp(cmd->beginlist->name, "") != 0 && verif_char(cmd->beginlist->name) == 1)
			{
				recup_argument(&st_tab, &st_env, &cmd->beginlist->name);
				if (!check_is_builtins(&st_tab))
					test_exist_fonction(&st_tab, &cmd->beginlist->name, &st_env);
				else if (check_is_builtins(&st_tab))
					realize_built(&st_tab, &st_env, &cmd->beginlist->name, env);
				forfree(st_tab.tab_word);
			}
			cmd->beginlist = cmd->beginlist->next;
		}*/
		free(line);
		/*while (list->next != NULL)
		  {
		  printf("LOL =%s\n", list->name);
		  list = list->next;
		  }*/
	}
	forfree(st_env.env);
	return (0);
}
