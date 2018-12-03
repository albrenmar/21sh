/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/03 15:18:51 by alsomvil         ###   ########.fr       */
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

int		search_symbol(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|' || cmd[i] == '&')
		{
			printf("Creation arbre pour ==>   %s   <==\n", cmd);
			//ft_create_tree(cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

t_tree	*ft_create_tree(char *cmd, t_tree *tree)
{
	int		i;
	int		mode;

	i = 0;
	mode = 1;
	while (cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|' && cmd[i] != '&')
	{
		i++;
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' && cmd[i + 1] == '<') || (cmd[i] == '|' && cmd[i + 1] == '|') || (cmd[i] == '&' && cmd[i + 1] == '&'))
			mode++;
	}
	tree->str1 = ft_strndup(cmd, i);
	tree->symbol = ft_strndup(&cmd[i], mode);
	i = i + mode;
	tree->str2 = ft_strdup(&cmd[i]);
	/*printf("str1 = %s\n", tree->str1);
	  printf("str2 = %s\n", tree->str2);
	  printf("symbole = %s\n", tree->symbol);
	  printf("\n");
	  printf("-----------------------------------------\n");
	  printf("\n");*/
	if (search_symbol(tree->str2))
	{
		tree->right = ft_memalloc(sizeof(t_tree));
		tree->right = ft_create_tree(tree->str2, tree->right);
	}
	return (tree);
}

void	apply_builtin(t_tab *st_tab, t_env *st_env, char *cmd, char **env)
{
		if (ft_strcmp(cmd, "") != 0 && verif_char(cmd) == 1)
		{
			recup_argument(st_tab, st_env, &cmd);
			if (!check_is_builtins(st_tab))
				test_exist_fonction(st_tab, &cmd, st_env);
			else if (check_is_builtins(st_tab))
				realize_built(st_tab, st_env, &cmd, env);
			forfree(st_tab->tab_word);
		}
}

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_cmd *cmd, char **env)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
	while (cmd->beginlist->name)
	{
		if (search_symbol(cmd->beginlist->name))
			tree = ft_create_tree(cmd->beginlist->name, tree);
		//SUITE
		else
		{
			//printf("la commande a lancer est : %s\n", cmd->beginlist->name);
			apply_builtin(st_tab, st_env, cmd->beginlist->name, env);
		}
		cmd->beginlist = cmd->beginlist->next;
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
		apply_cmd(&st_tab, &st_env, cmd, env);
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
