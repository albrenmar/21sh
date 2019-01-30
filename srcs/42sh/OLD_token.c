/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:18:22 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/26 04:18:48 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

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
