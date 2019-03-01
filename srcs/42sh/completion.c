/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:13:59 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/01 12:28:11 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		ft_valid_quote(char *line, char c)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0; 
	while (line[i])
	{
		if (line[i] == c)
			flag++;
		i++;
	}
	if ((flag % 2) == 0)
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
	int		test;

	ret = NULL;
	join = NULL;
	raccor = NULL;
	nb = 0;
	i++;
	while (line[i] && line[i] != '"')
		i++;
	if (!line[i])
	{
		*mv += i;
		ret = ft_strdup(line);
		saveprompt = g_tracking.prompt;
		g_tracking.prompt = ">";
		test = ft_valid_quote(ret, '"');
		while (test == 1)
		{
			g_tracking.quotes = 1;
			get_key();
			if (g_tracking.quotes == 10)
				exit (0);
			join = g_tracking.cmd;
			ret = ft_strjoinfree(ret, join, 3);
			test = ft_valid_quote(ret, '"');
			ft_putchar('\n');
		}
		g_tracking.quotes = 0;
		g_tracking.prompt = saveprompt;
		return (ret);
	}
	i++;
	while (line[i] && its_not_symbol(line[i]) && line[i] != ' ')
		i++;
	*mv += i;
	return (ft_strndup(line, i));
}

int		ft_valid_bracket(char *line, char c)
{
	int	flag;
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	flag = 1; 
	while (line[i])
	{
		//if (line[i] == c)
		//	flag++;
		if (line[i] == '"')
			quote++;
		if (line[i] == '}' && (quote % 2) == 0)
			flag--;
		i++;
	}
	if ((flag % 2) == 0)
		return (0);
	else
		return (1);
}

char	*check_bracket(char *line, int i, int *mv)
{
	char	*ret;
	char	*join;
	char	*raccor;
	char	*saveprompt;
	int		nb;
	int		test;

	ret = NULL;
	join = NULL;
	raccor = NULL;
	nb = 0;
	i++;
	while (line[i] && line[i] != '}')
		i++;
	if (!line[i])
	{
		*mv += i;
		ret = ft_strdup(line);
		saveprompt = g_tracking.prompt;
		g_tracking.prompt = ">";
		test = ft_valid_bracket(ret, '{');
		while (test == 1)
		{
			g_tracking.bracket = 1;
			get_key();
			if (g_tracking.bracket == 10)
				exit (0);
			join = g_tracking.cmd;
			raccor = check_quote(join, 0, &test);
			ret = ft_strjoinfree(ret, raccor, 3);
			test = ft_valid_bracket(ret, '{');
			ft_putchar('\n');
		}
		g_tracking.bracket = 0;
		//ft_putchar('\n');
		g_tracking.prompt = saveprompt;
		return (ret);
	}
	i++;
	while (line[i] && its_not_symbol(line[i]) && line[i] != ' ')
		i++;
	*mv += i;
	return (ft_strndup(line, i));
}
