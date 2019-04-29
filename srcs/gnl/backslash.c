/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 23:13:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/30 00:23:29 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	get_char(char c)
{
	if (c == '"')
		return (8);
	if (c == '\'')
		return (9);
	if (c == '\\')
		return (10);
	if (c == '!')
		return (11);
	if (c == '$')
		return (12);
	if (c == '|')
		return (13);
	if (c == '&')
		return (14);
	if (c == '>')
		return (15);
	if (c == '<')
		return (16);
	if (c == ' ')
		return (17);
	if (c == '*')
		return (18);
	if (c == '?')
		return (19);
	if (c == '{')
		return (20);
	if (c == '}')
		return (21);
	if (c == '=')
		return (22);
	return (c);
}

char	reset_char(char c)
{
	if (c == 8)
		return ('"');
	if (c == 9)
		return ('\'');
	if (c == 10)
		return ('\\');
	if (c == 11)
		return ('!');
	if (c == 12)
		return ('$');
	if (c == 13)
		return ('|');
	if (c == 14)
		return ('&');
	if (c == 15)
		return ('>');
	if (c == 16)
		return ('<');
	if (c == 17)
		return (' ');
	if (c == 18)
		return ('*');
	if (c == 19)
		return ('?');
	if (c == 20)
		return ('{');
	if (c == 21)
		return ('}');
	if (c == 22)
		return ('=');
	return (c);
}

char	*convert_backslash(char *line)
{
	char	*temp;
	int		i;

	if (!line)
		return(NULL);
	temp = line;
	i = 0;
	while (temp[i])
	{
		if (is_escape(temp, i))
			temp[i] = get_char(temp[i]);
		i++;
	}
	return (line);
}

char	*convert_back(char *line)
{
	char	*temp;
	int		i;

	if (!line)
		return(NULL);
	temp = line;
	i = 0;
	while (temp[i])
	{
		if (is_escape(temp, i))
			temp[i] = reset_char(temp[i]);
		i++;
	}
	return (temp);
}

char	*remove_back(char *line)
{
	char	*temp;
	int		i;
	int		a;

	if (!line)
		return(NULL);
	i = 0;
	a = 0;
	temp = ft_strnew(ft_strlen(line));
	{
		while (line[i])
		{
			if (line[i] == '\\' && is_escape(line, i) == 0)
			{
				if (line[i + 1])
					i++;
				else
					break;
			}
			temp[a] = line[i];
			i++;
			a++;
		}
	}
	ft_strdel(&line);
	return (temp);
}

