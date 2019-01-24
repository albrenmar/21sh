/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/23 23:49:46 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "job_control.h"
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

void	excute_ast(t_ast *ast_cmd)
{
	pid_t	pid1;
	pid_t	pid2;
	char *test[3];
	char *test2[3];

	test[0] = "grep";
	test[1] = "inc";
	test[2] = NULL;
	test2[0] = "ls";
	test2[1] = NULL;
	test2[2] = NULL;

	int		descrf[2];

	pipe(descrf);
	while (ast_cmd->next)
	{
		pid1 = fork();
		while (ast_cmd->next && ast_cmd->next_token == 1)
		{
			if (pid1 == 0)
			{
				dup2(descrf[ESCRIBIR], 1);
				close(descrf[LEER]);
				execve("/bin/ls", test2, NULL);
				perror("/bin/ls");
			}
			ast_cmd = ast_cmd->next;
		}
		wait(&pid1);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(descrf[LEER], 0);
			close(descrf[ESCRIBIR]);
			execve("/usr/bin/grep", test, NULL);
			//perror("/bin/ls");
		}
		close(descrf[0]);
		close(descrf[1]);
		wait(&pid2);
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
			//excute_ast(temp_ast);
			/*while (temp_ast->next)
			{
				printf("1 token = %d\n", temp_ast->next_token);
				printf("2 = %s\n", temp_ast->cmd);
				printf("3 = %s\n", temp_ast->next->cmd);
				temp_ast = temp_ast->next;
			}*/
		}
		else
			printf("%s%s\n", "Application du builtin si verif builtin:", list_cmd->name);
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
		list_cmd = list_cmd->next;
	}
}
