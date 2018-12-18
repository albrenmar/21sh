/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:26:41 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/17 04:36:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_symbol(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|' || cmd[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

t_tree	*ft_create_tree(char *cmd, t_tree *tree)
{
	int		i;
	int		mode;
	char	*tmp;
	char	*tmp2;
	t_split	split;

	i = 0;
	mode = 1;
	while (cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|' && cmd[i] != '&')
	{
		i++;
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || (cmd[i] == '<' &&
					cmd[i + 1] == '<') || (cmd[i] == '|' && cmd[i + 1] == '|')
				|| (cmd[i] == '&' && cmd[i + 1] == '&'))
			mode++;
	}
	tree->str1 = ft_strndup(cmd, i);
	tree->symbol = ft_strndup(&cmd[i], mode);
	tmp = ft_strtrim(tree->str1);
	tmp2 = prepare_new_string(tmp);
	tree->str_command1 = conv_whites_str(tmp2);
	ft_strdel(&tmp);
	tree->cmd1 = split_line(tree->str_command1, ' ', tmp2, &split);
	ft_strdel(&tmp2);
	tree->com_arg1 = count_com_arguments(tree->cmd1);
	i = i + mode;
	tree->str2 = ft_strdup(&cmd[i]);
	tmp = ft_strtrim(tree->str2);
	tmp2 = prepare_new_string(tmp);
	tree->str_command2 = conv_whites_str(tmp2);
	ft_strdel(&tmp);
	tree->cmd2 = split_line(tree->str_command2, ' ', tmp2, &split);
	ft_strdel(&tmp2);
	tree->com_arg2 = count_com_arguments(tree->cmd2);
	if (search_symbol(tree->str1))
	{
		tree->left = ft_memalloc(sizeof(t_tree));
		tree->left = ft_create_tree(tree->str1, tree->left);
	}
	else
		tree->left = NULL;
	if (search_symbol(tree->str2))
	{
		tree->right = ft_memalloc(sizeof(t_tree));
		tree->right = ft_create_tree(tree->str2, tree->right);
	}
	else
		tree->right = NULL;
	/* AJOUT FONCTION MJOSE */
// Tu peux recuperer ici tree->str1, tree->str2 et tree->symbol pour tes tests
	/* AJOUT FONCTION MJOSE */


	/* FINI DEMAIN */
	/* FINI DEMAIN */

	return (tree);
}
