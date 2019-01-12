/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:28:29 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/12 04:47:48 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# define LEER		0
# define ESCRIBIR	1
# define SYMBOL cmd_full[i] == '<' || cmd_full[i] == '>' || cmd_full[i] == '|' || cmd_full[i] == '&'
# define SYMBOL_TWO cmd_full[i + 1] == '<' || cmd_full[i + 1] == '>' || cmd_full[i + 1] == '|' || cmd_full[i + 1] == '&'

void	tokenisation(char *symbol, int token, int mode)
{
	if (mode == 1)
	{
		if (symbol[0] == '|')
			token = 1;
		if (symbol[0] == '>')
			token = 2;
		if (symbol[0] == '<')
			token = 3;
		if (symbol[0] == '&')
			token = 4;
		return ;
	}
	if (mode == 2)
	{
		if (symbol[0] == '|' && symbol[1] == '|')
			token = 5;
		else if (symbol[0] == '>' && symbol[1] == '>')
			token = 6;
		else if (symbol[0] == '<' && symbol[1] == '<')
			token = 7;
	}
}

t_ast	*new_first_list(void)
{
	t_ast	*list_cmd;

	list_cmd = ft_memalloc(sizeof(t_ast));
	list_cmd->cmd = NULL;
	list_cmd->next_token = 0;
	list_cmd->next = NULL;
	list_cmd->prev = NULL;
	return (list_cmd);
}

void	create_ast(char *cmd_full)
{
	t_ast	*list_cmd;
	int		i;

	i = 0;
	list_cmd = new_first_list();
	printf("TEST\n");
	while (cmd_full[i])
	{
		if (SYMBOL)
		{
			list_cmd->cmd = ft_strndup(cmd_full, i);
			if (SYMBOL_TWO)
			{
				tokenisation(&cmd_full[i - 1], list_cmd->next_token, 2);
				i++;
			}
			else
				tokenisation(&cmd_full[i - 1], list_cmd->next_token, 1);
		}
		i++;
	}


}

void	apply_cmd(t_tab *st_tab, t_env *st_env, t_last *list_cmd)
{
	while (list_cmd->name)
	{
		if (search_symbol(list_cmd->name))
			create_ast(list_cmd->name);
		else
			apply_builtin(st_tab, st_env, list_cmd->name);
		list_cmd = list_cmd->next;
	}
}
