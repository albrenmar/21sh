/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/31 06:58:36 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		create_ast(t_tree *tree, t_last *list)
{
	t_last *temp;

	temp = NULL;
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if ((temp == NULL) && list->type == OP)
			temp = list;
		else if (list->type == OP)
		{
			if (list->name[0] == ';' || list->name[0] == '&')
				temp = list;
		}
		list = list->prev;
	}
	printf("name = %s\n", temp->name);
	exit (0);
	return ;
}

void		ft_ast(t_last *list)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
	create_ast(tree, list);
	return ;
}
