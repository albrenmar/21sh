/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:26:41 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/12 04:47:54 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

# define SYMBOL cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|' || cmd[i] == '&'

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


/*t_tree	*ft_create_tree(char *cmd, t_tree *tree)
{
	int		i;
	int		end;
	int		mode;

	i = 0;
	end = ft_strlen(cmd) - 1;
	mode = 1;
	//printf("END = %d\n", end);
	while (end > 0 && SYMBOL)
		end--;
	if (end > 0)
		end--;
	if (!(SYMBOL))
		mode = 2;
	if (mode == 1)
	{
		tree->str1 = ft_strndup(cmd, ft_strlen(cmd) - ft_strlen(&cmd[end + 1]));
		tree->str2 = ft_strdup(&cmd[end + 2]);
		tree->symbol = ft_strndup(&cmd[end + 1], mode);
	}
	if (mode == 2)
	{
		tree->str1 = ft_strndup(cmd, ft_strlen(cmd) - ft_strlen(&cmd[end]));
		tree->str2 = ft_strdup(&cmd[end + mode]);
		tree->symbol = ft_strndup(&cmd[end], mode);
	}
	printf("Symbol = %s\n", tree->symbol);
	printf("Str1 = %s\n", tree->str1);
	printf("Str2 = %s\n", tree->str2);
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
	return (tree);
}*/
