/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/28 05:28:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		its_not_symbol(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';')
		return (0);
	else
		return (1);
}

char	*check_quote(char *line, int i, int *mv)
{
	char	*ret;
	char	*join;
	char	*raccor;
	char	*saveprompt;
	int		nb;

	ret = NULL;
	join = NULL;
	raccor = NULL;
	nb = 0;
	i++;
	while (line[i] && line[i] != '"')
		i++;
	if (!line[i])
	{
		printf("IL FAUT FINIR LA LIGNE MALHEU\n");
		*mv += i;
		ret = ft_strndup(line, i);
		saveprompt = g_tracking.prompt;
		g_tracking.prompt = ">";
		get_key();
		join = g_tracking.cmd;
		raccor = ft_strjoin(ret, join);
		g_tracking.prompt = saveprompt;
		ft_putchar('\n');
		return (raccor);
	}
	i++;
	while (line[i] && its_not_symbol(line[i]) && line[i] != ' ')
		i++;
	*mv += i;
	return (ft_strndup(line, i));
}


char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line)
		return (NULL);
	while (line[nb] == ' ')
	{
		(*i)++;
		nb++;
	}
	if (line[nb] == '"')
		return (check_quote(&line[nb], 0, i));
	else if ((test = search_fd_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_symboll(&line[nb], i)))
		return (test);
	else
		test = search_normally_arg(&line[nb], i);
	return (test);
}


t_last	*ft_parseur(char *line)
{
	char	*temp;
	int		i;
	t_last	*list_cmd;
	t_last	*templist;

	i = 0;
	temp = NULL;
	while (line[i] == ' ')
		i++;
	if ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		list_cmd = create_new_list();
		templist = list_cmd;
		list_cmd->name = temp;
		temp = NULL;
		//ATTENTION !! SEGFAULT ICI DANS LE CAS "dsf
		while (line[i] && (temp = recup_cmd(&line[i], &i, 0)) != NULL)
		{
			list_cmd->next = create_new_list();
			list_cmd->next->prev = list_cmd;
			list_cmd = list_cmd->next;
			list_cmd->name = ft_strdup(temp);
			free(temp);
		}
		list_cmd->next = NULL;
		list_cmd = templist;
	}
	else
		return (NULL);
	//print_last(list_cmd);
	ft_lexeur(list_cmd);
	if (error_lexer(list_cmd))
		return (NULL);
	return (list_cmd);
}
