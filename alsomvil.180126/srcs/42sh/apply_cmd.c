/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/25 06:31:49 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"
# define LEER		0
# define ESCRIBIR	1
# define SYMBOL (cmd_full[i] && (cmd_full[i] == '<' || cmd_full[i] == '>' || cmd_full[i] == '|' || cmd_full[i] == '&'))
# define SYMBOL_TWO cmd_full[i + 1] && (cmd_full[i + 1] == '<' || cmd_full[i + 1] == '>' || cmd_full[i + 1] == '|' || cmd_full[i + 1] == '&')

void	tokenisation(char *symbol, int *token, int mode)
{
	if (mode == 1)
	{
		if (symbol[0] == '|')
			*token = 1;
		if (symbol[0] == '>')
			*token = 2;
		if (symbol[0] == '<')
			*token = 3;
		if (symbol[0] == '&')
			*token = 4;
		return ;
	}
	if (mode == 2)
	{
		if (symbol[0] == '|' && symbol[1] == '|')
			*token = 5;
		else if (symbol[0] == '>' && symbol[1] == '>')
			*token = 6;
		else if (symbol[0] == '<' && symbol[1] == '<')
			*token = 7;
	}
}

t_ast	*new_first_list(t_ast *ast_cmd, int mode)
{

	if (mode == 0)
	{
		ast_cmd = ft_memalloc(sizeof(t_ast));
		ast_cmd->cmd = NULL;
		ast_cmd->next_token = 0;
		ast_cmd->next = NULL;
		ast_cmd->prev = NULL;
	}
	else
	{
		ast_cmd->next = ft_memalloc(sizeof(t_ast));
		ast_cmd->next->prev = ast_cmd;
		ast_cmd = ast_cmd->next;
		ast_cmd->cmd = NULL;
		ast_cmd->next_token = 0;
		ast_cmd->next = NULL;
	}
	return (ast_cmd);
}

void	create_ast(char *cmd_full, t_ast *ast_cmd)
{
	unsigned int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < (ft_strlen(cmd_full) + 1))
	{
		if (SYMBOL || cmd_full[i] == '\0')
		{
			ast_cmd->cmd = ft_strndup(cmd_full, i);
			if (cmd_full[i] == '\0')
				return ;
			else if (SYMBOL_TWO)
			{
				tokenisation(&cmd_full[i], &ast_cmd->next_token, 2);
				temp = ft_strdup(&cmd_full[i + 2]);
			}
			else
			{
				tokenisation(&cmd_full[i], &ast_cmd->next_token, 1);
				temp = ft_strdup(&cmd_full[i + 1]);
			}
			free(cmd_full);
			cmd_full = temp;
			new_first_list(ast_cmd, 1);
			create_ast(cmd_full, ast_cmd->next);
			return ;
		}
		i++;
	}
}

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

char	**test_exist_fonction(char **tab_cmd, char **pathlist)
{
	int		i;

	i = 0;
	if ((access(tab_cmd[0], X_OK) == 0) || (test_exist_fonction_two(&tab_cmd, pathlist) == 1))
	{
		return (tab_cmd);
	}
	else
	{
		printf("La commande %s n'existe pas\n", tab_cmd[i]);
		return (NULL);
	}
	return (NULL);
}

char	**cmd_to_tab(t_ast *ast_cmd, char **pathlist)
{
	char	**tab_cmd;

	if (ast_cmd->cmd && ft_strcmp(ast_cmd->cmd, "") != 0)
		tab_cmd = ft_strsplit(ast_cmd->cmd, ' ');
	test_exist_fonction(tab_cmd, pathlist);
	return (tab_cmd);
}

void	execute_pipe_one(t_ast *ast_cmd)
{
	pid_t	pid1;
	char	**tab_cmd;
	int		descrf[2];
	int		i;
	char	*path;
	char	**tablist;

	i = 0;
	path = get_env_string("PATH");
	tablist = ft_strsplit(path, ':');
	tab_cmd = cmd_to_tab(ast_cmd, tablist);
	pipe(descrf);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(descrf[ESCRIBIR], 1);
		close(descrf[LEER]);
		execve(tab_cmd[0], tab_cmd, NULL);
		perror(tab_cmd[0]);

	}
	wait(&pid1);
}

void	execute_end_cmd(t_ast *ast_cmd, int *descrf_two, char **tablist)
{
	pid_t	pid1;
	char	**tab_cmd;

	if (ast_cmd && (ast_cmd->next_token == 0))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf_two[LEER], 0);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		close(descrf_two[0]);
		close(descrf_two[1]);
		//close(descrf[0]);
		//close(descrf[1]);
		wait(&pid1);
	}
}

void	execute_pipe_two(t_ast *ast_cmd, int *descrf, char **tablist)
{
	pid_t	pid1;
	int		descrf_two[2];
	char	**tab_cmd;

	pipe(descrf_two);
	if (ast_cmd && (ast_cmd->next_token == 1))
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[LEER], 0);
			dup2(descrf_two[ESCRIBIR], 1);
			close(descrf_two[LEER]);
			close(descrf[ESCRIBIR]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
	}
	descrf[LEER] = descrf_two[LEER];
	close(descrf_two[ESCRIBIR]);
}

void	excute_ast(t_ast *ast_cmd)
{
	pid_t	pid1;
	char	**tab_cmd;
	int		descrf[2];
	char	*path;
	char	**tablist;

	path = get_env_string("PATH");
	tablist = ft_strsplit(path, ':');
	pipe(descrf);
	if (ast_cmd->next_token == 1)
	{
		tab_cmd = cmd_to_tab(ast_cmd, tablist);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(descrf[ESCRIBIR], 1);
			close(descrf[LEER]);
			execve(tab_cmd[0], tab_cmd, NULL);
			perror(tab_cmd[0]);
		}
		wait(&pid1);
		ast_cmd = ast_cmd->next;
		close(descrf[ESCRIBIR]);
		while (ast_cmd->next && ast_cmd->next_token == 1)
		{
			execute_pipe_two(ast_cmd, descrf, tablist);
			ast_cmd = ast_cmd->next;
		}
		execute_end_cmd(ast_cmd, descrf, tablist);
	}
}

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_last *list_cmd)
{
	t_ast	*ast_cmd;
	t_ast	*temp_ast;

	ast_cmd = NULL;
	ast_cmd = new_first_list(ast_cmd, 0);
	temp_ast = ast_cmd;
	while (list_cmd && list_cmd->name)
	{
		/*printf("%s\n", list_cmd->name);
		  printf("-------------------------------\n");*/
		if (search_symbol(list_cmd->name))
		{
			create_ast(list_cmd->name, ast_cmd);
			excute_ast(temp_ast);
			list_cmd = list_cmd->next;
			/*while (temp_ast->next)
			  {
			  printf("1 token = %d\n", temp_ast->next_token);
			  printf("2 = %s\n", temp_ast->cmd);
			  printf("3 = %s\n", temp_ast->next->cmd);
			  temp_ast = temp_ast->next;
			  }*/
		}
		else
		{
			printf("%s%s\n", "Application du builtin si verif builtin:", list_cmd->name);
			list_cmd = list_cmd->next;
		}
		//apply_builtin(st_tab, st_env, list_cmd->name);
		/*printf("1 = %s\n", temp_ast->cmd);
		  printf("1 token = %d\n", temp_ast->next_token);
		  printf("------------------------------\n");
		  printf("2 = %s\n", temp_ast->next->cmd);
		  printf("2 token = %d\n", temp_ast->next->next_token);
		  printf("------------------------------\n");
		  printf("3 = %s\n", temp_ast->next->next->cmd);
		  printf("3 token = %d\n", temp_ast->next->next->next_token);
		  printf("|\n");
		  printf("|\n");
		  printf("|\n");*/
		//list_cmd = list_cmd->next;
	}
}
