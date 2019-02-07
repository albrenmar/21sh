/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/07 06:47:27 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int		test_exist_fonction_two(char ***tab_cmd, char **pathlist)
{
	int		i;
	char	*next_str;
	char	*addslash;

	i = 0;
	next_str = NULL;
	while (pathlist[i])
	{
		addslash = ft_strjoin(pathlist[i], "/");
		next_str = ft_strjoin(addslash, *tab_cmd[0]);
		if (access(next_str, X_OK) == 0)
		{
			free(*tab_cmd[0]);
			*tab_cmd[0] = ft_strdup(next_str);
			free(addslash);
			free(next_str);
			return (1);
		}
		i++;
		free(addslash);
		free(next_str);
	}
	return (0);
}

char	**test_exist_fonction(char **tab_cmd)
{
	int		i;
	char	**pathlist;
	char	*path;

	i = 0;
	path = get_env_string("PATH");
	pathlist = ft_strsplit(path, ':');
	if ((access(tab_cmd[0], X_OK) == 0) || (test_exist_fonction_two(&tab_cmd, pathlist) == 1))
		return (tab_cmd);
	else
	{
		printf("La commande %s n'existe pas\n", tab_cmd[i]);
		return (NULL);
	}
	return (NULL);
}

void		execute_four(void)
{
	g_tracking.mysh->exec->left = test_exist_fonction(g_tracking.mysh->exec->left);

	execve(g_tracking.mysh->exec->left[0], g_tracking.mysh->exec->left, NULL);
	perror(g_tracking.mysh->exec->left[0]);
}

void		execute_two(void)
{
	g_tracking.mysh->exec->left = test_exist_fonction(g_tracking.mysh->exec->left);
	execve(g_tracking.mysh->exec->left[0], g_tracking.mysh->exec->left, NULL);
	perror(g_tracking.mysh->exec->left[0]);
}

void		execute_pipe_two(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		dprintf(2, "PID fils = %d\n", getpid());
		close(descrf_two[1]);
		dup2(descrf_two[0], 0);
		close(descrf_two[0]);
		execute_four();
	}
	else
	{
		close(descrf_two[0]);
		wait(NULL);
	}
}

void		execute_pipe(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
		execute_two();
	}
	else
	{
		close(descrf_two[1]);
		wait(NULL);
	}
}

void		execute(void)
{
	if (g_tracking.mysh->exec->sym[0][0] == '|')
	{
		if (ft_strlen(g_tracking.mysh->exec->sym[0]) != 2)
		{
			descrf[0] = descrf_two[0];
			descrf[1] = descrf_two[1];
			pipe(descrf_two);
			execute_pipe();

		}
		else
		{
			execute_pipe_two();
			close(descrf[0]);
			close(descrf[1]);
			close(descrf_two[0]);
			close(descrf_two[1]);
		}
	}
	else if (g_tracking.mysh->exec->sym[0][0] == '>')
	{
		printf("%s\n", "test de fou");
		exit (0);
	}
}

void		execute_ast(t_tree *tree, t_tab_arg *tab_arg)
{
	if (tree->left)
		execute_ast(tree->left, tab_arg);
	if (!g_tracking.mysh->exec->sym && tree->type == OP)
	{
		/*if ((tree->name[0] == '|' || tree->name[0] == '&') && ft_strlen(tree->name) == 2)//symbole == || ou &&)
		  {
		  g_tracking.mysh->exec->left = NULL; //droite est NULL;
		  g_tracking.mysh->exec->right = NULL;//gauche est NULL;
		  }*/
		//else if (tree->type == OP)
		g_tracking.mysh->exec->sym = tree->cmd;//enregistre symbole;
	}
	if ((!g_tracking.mysh->exec->left || !g_tracking.mysh->exec->right) && !tree->left)//!temp gauche || !temp droite) et pas de branche gauche)
	{
		if (!g_tracking.mysh->exec->left)//!temp gauche)
			g_tracking.mysh->exec->left = tree->cmd;//enregistrer gauche;
		else
			g_tracking.mysh->exec->right = tree->cmd;//enregistrer droite;
	}
	if (g_tracking.mysh->exec->left && g_tracking.mysh->exec->right) //temp gauche et temp droite)
	{
		//printf("J'execute %s avec %s\n", g_tracking.mysh->exec->left[0], g_tracking.mysh->exec->sym[0]);
		execute();
		g_tracking.mysh->exec->left = g_tracking.mysh->exec->right;//gauche devient droite;
		g_tracking.mysh->exec->right = NULL;// est NULL;
		g_tracking.mysh->exec->sym = NULL;//symbole est NULL;
		return ;
	}
	if (!g_tracking.mysh->exec->sym && tree->type == OP && (ft_strlen(tree->name) != 2 || (tree->name[0] != '|' && tree->name[0] != '&'))) //pas de symbole et symbole different de || ou &&)
		g_tracking.mysh->exec->sym = tree->cmd;//enregistre symbole;
	if (tree->right)//branche droite)
		execute_ast(tree->right, tab_arg);
	return ;
}
