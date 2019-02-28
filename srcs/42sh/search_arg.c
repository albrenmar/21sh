/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:06:56 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/27 18:40:44 by alsomvil         ###   ########.fr       */
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
		(*nb) += i;
		ret = ft_strndup(str, i);
		return (ret);
	}
	else if (str[i] == ';')
	{
		(*nb)++;
		return (ft_strndup(str, 1));
	}
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
			(*nb) += i;
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
		(*nb) += i;
		ret = ft_strndup(str, i);
		return (ret);
	}
	return (NULL);
}

char	*search_normally_arg(char *str, int *nb)
{
	int		i;
	char	*join;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] && its_not_symbol(str[i]) && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			join = check_quote(&str[i], 0, nb);
		}
		i++;
	}
	(*nb) += i;
	if (i > 0)
		ret = ft_strndup(str, i);
	return (ret);
}
