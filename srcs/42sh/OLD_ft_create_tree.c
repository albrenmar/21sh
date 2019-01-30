/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:26:41 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/21 18:17:00 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
