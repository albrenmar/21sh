/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:09:45 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/26 06:33:36 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"
# define SYMBOL (cmd_full[i] && (cmd_full[i] == '<' || cmd_full[i] == '>' || cmd_full[i] == '|' || cmd_full[i] == '&'))
# define SYMBOL_TWO cmd_full[i + 1] && (cmd_full[i + 1] == '<' || cmd_full[i + 1] == '>' || cmd_full[i + 1] == '|' || cmd_full[i + 1] == '&')

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
	char	*path;
	char	**tablist;

	path = get_env_string("PATH");
	tablist = ft_strsplit(path, ':');
	if (ast_cmd->next_token == 1)
		execute_first_pipe(ast_cmd, tablist);
	else if (ast_cmd->next_token == 2)
		printf("%s\n", "Execution d'une redirection");
		//execute_first_redir(ast_cmd, tablist);
}
