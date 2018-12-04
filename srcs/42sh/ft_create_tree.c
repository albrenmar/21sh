/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:26:41 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 18:21:56 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	i = i + mode;
	tree->str2 = ft_strdup(&cmd[i]);


	/* AJOUT FONCTION MJOSE */
// Tu peux recuperer ici tree->str1, tree->str2 et tree->symbol pour tes tests
	/* AJOUT FONCTION MJOSE */


	/* FINI DEMAIN */
//if (search_symbol(tree->str2))
//{
//tree->right = ft_memalloc(sizeof(t_tree));
//tree->right = ft_create_tree(tree->str2, tree->right);
//}
	/* FINI DEMAIN */

	return (tree);
}
