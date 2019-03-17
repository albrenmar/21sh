/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:06:56 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/17 04:18:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

char	*search_symboll(char *str, int *nb)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] && (str[i] == '|' || str[i] == '&'))
	{
		i++;
		if (str[i] && str[i] == str[i - 1])
			i++;
		ret = ft_strndup(str, i);
		return (ret);
	}
	else if (str[i] == ';')
		return (ft_strndup(str, 1));
	return (NULL);
}

char	*search_fd_reddir(char *str, int *nb)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		i++;
		if (str[i] && (str[i] == '>' || str[i] == '<'))
		{
			i++;
			if (str[i] && str[i] == str[i - 1])
				i++;
			if (str[i] && str[i] == '&')
				i++;
			ret = ft_strndup(str, i);
			return (ret);
		}
	}
	return (NULL);
}

char	*search_reddir(char *str, int *nb)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] && (str[i] == '>' || str[i] == '<'))
	{
		i++;
		if (str[i] && str[i] == str[i - 1])
			i++;
		if (str[i] && str[i] == '&')
			i++;
		ret = ft_strndup(str, i);
		return (ret);
	}
	return (NULL);
}

char	*search_normally_arg(char *str, int *nb)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if (str[i] && str[i] == '"')
		{
			temp = its_quote(i, str, nb, '"');
			if (temp)
				return (temp);
		}
		else if (str[i] && str[i] == '\'')
		{
			temp = its_quote(i, str, nb, '\'');
			if (temp)
				return (temp);
		}
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{')
		{
			i++;
			while (str[i] && str[i] != '}')
				i++;
			i++;
			if (!str[i] || str[i] == ' ')
			{
				temp = ft_strndup(str, i);
				return (temp);
			}
		}
		else if (str[i] == ' ' || !its_not_symbol(str[i]))
		{
			temp = ft_strndup(str, i);
			return (temp);
		}
		else
			i++;
	}
	temp = ft_strndup(str, i);
	return (temp);
}
