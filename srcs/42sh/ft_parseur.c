/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/14 11:06:45 by alsomvil         ###   ########.fr       */
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
	if ((test = search_fd_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_reddir(&line[nb], i)))
		return (test);
	else if ((test = search_symboll(&line[nb], i)))
		return (test);
	else
		test = search_normally_arg(&line[nb], i);
	return (test);
}

char	*ft_modif_line(char **line)
{
	int		i;
	int		j;
	int		k;
	char	*new_line;
	char	*temp;

	i = 0;
	j = 0;
	new_line = NULL;
	temp = NULL;
	if (ft_valid_quote(*line, '"', 0))
	{
		temp = check_quote(*line, 0, '"');
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
		return (NULL);
	}
	else if (ft_valid_quote(*line, '\'', 0))
	{
		temp = check_quote(*line, 0, '\'');
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
		return (NULL);
	}
	else if (ft_valid_bracket(*line, '}', 0))
	{
		temp = check_bracket(*line, 0);
		new_line = ft_strjoin(*line, temp);
		*line = new_line;
		return (NULL);
	}
	else
		new_line = ft_strdup(*line);
	return (new_line);
}

t_last	*ft_parseur(char *str)
{
	char	*temp;
	int		i;
	char	*line;
	t_last	*list_cmd;
	t_last	*templist;

	i = 0;
	temp = NULL;
	line = NULL;
	list_cmd = NULL;
	while (str[i] == ' ')
		i++;
	while ((line = ft_modif_line(&str)) == NULL)
		;
	if ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		i += ft_strlen(temp);
		list_cmd = create_new_list();
		templist = list_cmd;
		list_cmd->name = temp;
		temp = NULL;
		while (line[i] && (temp = recup_cmd(&line[i], &i, 0)) != NULL)
		{
			i += ft_strlen(temp);
			list_cmd->next = create_new_list();
			list_cmd->next->prev = list_cmd;
			list_cmd = list_cmd->next;
			list_cmd->name = ft_strdup(temp);
		}
		list_cmd->next = NULL;
		list_cmd = templist;
	}
	else
		return (NULL);
	ft_lexeur(list_cmd);
	//print_last(list_cmd);
	if (error_lexer(list_cmd))
		return (NULL);
	return (list_cmd);
}
