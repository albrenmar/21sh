/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:41:13 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 10:28:26 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int		error_lexer(t_last *list_cmd)
{
	if (list_cmd && list_cmd->type == OP && !its_reddir(list_cmd) && !its_fd_reddir(list_cmd))
	{
		printf("Error\n");
		return (1);
	}
	while (list_cmd)
	{
		if (list_cmd->type == OP && list_cmd->next && list_cmd->next->type == OP)
		{
			if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == ';')
			{
				if (list_cmd->next->next && (((ft_strlen(list_cmd->next->name) == 1) && ft_strlen(list_cmd->next->next->name) == 2)
							|| ((ft_strlen(list_cmd->next->name) == 2) && (list_cmd->next->next && list_cmd->next->next->type == OP))))
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == '&')
			{
				printf("Error\n");
				return (1);
			}
			else if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == '>')
			{
				if (ft_strlen(list_cmd->next->name) == 2 || list_cmd->next->name [0] == '>' || list_cmd->next->name[0] == ';' || (list_cmd->next->next && list_cmd->next->next->type == OP))
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == '<')
			{
				if (ft_strlen(list_cmd->next->name) == 2 || list_cmd->next->name [0] == '<' || list_cmd->next->name[0] == ';' || (list_cmd->next->next && list_cmd->next->next->type == OP))
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] == ';')
			{
				printf("Error\n");
				return (1);
			}
			else if (ft_strlen(list_cmd->name) == 2 || (list_cmd->next && ft_strlen(list_cmd->next->name) == 2))
			{
				if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] == '|' && list_cmd->next->next && list_cmd->next->next->type == OP)
				{
					printf("Error\n");
					return (1);
				}
				else if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] != '|')
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (list_cmd->next->next && (list_cmd->next->next->type == OP))
			{
				printf("Error\n");
				return (1);
			}
		}
		list_cmd = list_cmd->next;
	}
	return (0);
}

void	ft_lexeur(t_last *list_cmd)
{
	int		i;

	i = 0;
	while (list_cmd)
	{
		if (list_cmd->name[0] > 47 && list_cmd->name[0] < 58)
		{
			while (list_cmd->name[i] > 47 && list_cmd->name[i] < 58)
				i++;
			if ((list_cmd->name[i] == '>' || list_cmd->name[i] == '<') && list_cmd->name[i + 1] && list_cmd->name[i + 1] == '&')
			{
				list_cmd->type = DESCR;
				list_cmd = list_cmd->next;
			}
			else if (list_cmd->name[i] == '>' || list_cmd->name[i] == '<')
			{
				list_cmd->type = OP;
				list_cmd = list_cmd->next;
			}
			else
			{
				if (!list_cmd->prev || (list_cmd->prev && (list_cmd->prev->type == OP || list_cmd->prev->type == DESCR)))
					list_cmd->type = CMD;
				else
					list_cmd->type = ARG;
				list_cmd = list_cmd->next;
			}
		}
		else if (list_cmd->name[0] == ';' || list_cmd->name[0] == '|' || list_cmd->name[0] == '>' || list_cmd->name[0] == '<' || list_cmd->name[0] == '&')
		{
			list_cmd->type = OP;
			list_cmd = list_cmd->next;
		}
		else if (!list_cmd->prev || (list_cmd->prev && (list_cmd->prev->type == OP)))
		{
			list_cmd->type = CMD;
			list_cmd = list_cmd->next;
		}
		else if (list_cmd->prev && list_cmd->prev->type == CMD && list_cmd->name[0] == '-')
		{
			list_cmd->type = OPT;
			list_cmd = list_cmd->next;
		}
		else
		{
			list_cmd->type = CMD;
			list_cmd = list_cmd->next;
		}
	}
}
