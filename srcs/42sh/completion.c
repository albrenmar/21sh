/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:13:59 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/08 02:29:14 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		ft_valid_quote(char *line, char c, int flag)
{
	int		i;
	int		chaine;
	char	temp;

	i = 0;
	chaine = 0;
	if (c == '"')
		temp = '\'';
	else if (c == '\'')
		temp = '"';
	while (line[i])
	{
		if (line[i] == temp && flag == 0)
		{
			i++;
			chaine++;
			while (line[i] && line[i] != temp)
				i++;
			if (!line[i])
				return (0);
			else
				chaine--;
		}
		else if (line[i] == c && !flag && !chaine)
			flag++;
		else if (line[i] == c && flag)
			flag--;
		i++;
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}

char	*check_quote(char *line, int i, char c)
{
	char	*ret;
	char	*join;
	char	*raccor;
	int		nb;
	int		test;

	ret = NULL;
	join = NULL;
	raccor = NULL;
	nb = 0;
	test = 1;
	i++;
	while (line[i])
		i++;
	while (test == 1)
	{
		if (c == '"')
			g_tracking.quotes = 1;
		if (c == '\'')
			g_tracking.quotes = 2;
		get_key();
		if (g_tracking.quotes == 10)
			exit (0);
		join = g_tracking.cmd;
		test = ft_valid_quote(join, c, test);
		if (!ret)
			ret = ft_strdup(join);
		else
		{
			raccor = ft_strjoin(ret, join);
			ret = raccor;
		}
		ft_putchar('\n');
	}
	g_tracking.quotes = 0;
	return (ret);
}

int		ft_valid_bracket(char *line, char c, int flag)
{
	int	i;
	int	accol;
	int	quote;
	int double_quote;
	
	i = 0;
	accol = 0;
	quote = 0;
	double_quote = 0;
	while (line[i])
		i++;
	while (i > 0)
	{
		if (line[i] == '"')
			double_quote++;
		else if (line[i] == '\'')
			quote++;
		else if (line[i] == '}' && quote % 2 == 0 && double_quote % 2 == 0)
			accol++;
		else if (line[i] == '$' && line[i + 1] && line[i + 1] == '{' && quote % 2 == 0 && double_quote % 2 == 0)
		{
			accol--;
			if (accol < 0)
				return (1);
		}
		i--;
	}
	return (0);
}

char	*check_bracket(char *line, int i)
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
	test = 1;
	i++;
	while (line[i])
		i++;
	saveprompt = g_tracking.prompt;
	g_tracking.prompt = ">";
	if (test == 1)
	{
		g_tracking.bracket = 1;
		get_key();
		if (g_tracking.bracket == 10)
			exit (0);
		join = g_tracking.cmd;
		test = ft_valid_bracket(join, '{', test);
		if (!ret)
			ret = ft_strdup(join);
		else
		{
			raccor = ft_strjoin(ret, join);
			ret = raccor;
		}
		ft_putchar('\n');
	}
	g_tracking.bracket = 0;
	g_tracking.prompt = saveprompt;
	return (ret);
}
