/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/31 13:10:14 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_quote(char *line, int *i, int *nb)
{
	printf("%s\n", "modification de la commande sans quote");
	exit (0);
	return (line);
}

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line[nb])
		return (NULL);
	if (line[nb] == '\'' || line[nb] == '\"')
		return (check_quote(line, i, &nb));
	while (line[nb])
	{
		if (line[nb] == ';' || line[nb] == '|' || line[nb] == '&' || line[nb] == '>' || line[nb] == '<' || line[nb] == '(' || line[nb] == ')')
		{
			if (line[nb + 1] && (line[nb + 1] == line[nb]))
			{
				test = ft_strndup(line, 2);
				(*i) = (*i) + 2;
				nb = nb + 2;
			}
			else
			{
				test = ft_strndup(line, 1);
				(*i) = (*i) + 1;
				nb = nb + 1;
			}
		}
		else
		{
			while (line[nb] && line[nb] != ' ' && line[nb] != ';' && line[nb] != '|' && line[nb] != '&' && line[nb] != '>' && line[nb] != '<' && line[nb] != '(' && line[nb] != ')')
			{
				nb++;
				(*i)++;
			}
			test = ft_strndup(line, nb);
		}
		while (line[nb++] == ' ')
			(*i)++;
		return (test);
	}
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
		list_cmd->name = ft_strdup(temp);
		free(temp);
		while ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
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
	ft_lexeur(list_cmd);
	if (error_lexer(list_cmd))
		return (NULL);
	if (list_cmd)
		tri_lexer(list_cmd);
	return (list_cmd);
}
