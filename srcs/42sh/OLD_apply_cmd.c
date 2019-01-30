/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/26 04:32:12 by alsomvil         ###   ########.fr       */
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

char	**test_exist_fonction(char **tab_cmd, char **pathlist)
{
	int		i;

	i = 0;
	if ((access(tab_cmd[0], X_OK) == 0) || (test_exist_fonction_two(&tab_cmd, pathlist) == 1))
		return (tab_cmd);
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

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_last *list_cmd)
{
	t_ast	*ast_cmd;
	t_ast	*temp_ast;

	ast_cmd = NULL;
	ast_cmd = new_first_list(ast_cmd, 0);
	temp_ast = ast_cmd;
	while (list_cmd && list_cmd->name)
	{
		if (search_symbol(list_cmd->name))
		{
			create_ast(list_cmd->name, ast_cmd);
			excute_ast(temp_ast);
			list_cmd = list_cmd->next;
		}
		else
		{
			printf("%s%s\n", "Application du builtin si verif builtin:", list_cmd->name);
			list_cmd = list_cmd->next;
		}
	}
}
