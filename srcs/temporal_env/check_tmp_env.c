/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tmp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 03:49:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temporal_env.h"
#include "sh21.h"

int				is_env_alone_check(char *str, int jsave)
{
	while (str[jsave] && is_spaces(str, jsave, 2))
		jsave++;
	while (str[jsave] && !is_spaces(str, jsave, 2))
		jsave++;
	if (!str[jsave])
		return (1);
	while (str[jsave] && is_spaces(str, jsave, 1))
		jsave++;
	if (!str[jsave])
		return (1);
	while (str[jsave] != '\0')
	{
		if (!is_spaces(str, jsave, 1))
			return (is_env_alone_check_helper(str, jsave, 0));
		jsave++;
	}
	return (1);
}

char			*swap_env_var(char *str, int jsave, int cmdindex)
{
	int			save;

	save = jsave;
	while (jsave > 0 && !is_spaces(str, jsave, 3))
		jsave--;
	if (jsave != 0 || (jsave == 0 && str[jsave] && is_spaces(str, jsave, 1)))
		jsave++;
	if (is_env_alone_check(str, jsave))
		return (str);
	save_tmp_env(str, jsave, cmdindex);
	return (clean_line_tmpenv(str, jsave, 0));
}

char			*check_if_swap_env(char **taab, char *line, int i, int cmdindex)
{
	int			j;

	while (taab[i] != NULL)
	{
		j = 0;
		while (taab[i][j] && is_spaces(taab[i], j, 2))
			j++;
		if (taab[i][j] && taab[i][j] == '$')
		{
			cmdindex++;
			i++;
			continue ;
		}
		taab[i] = check_if_env_option_i(taab, i, j, cmdindex);
		cmdindex++;
		i++;
	}
	return (check_if_swap_helper(taab, 0, line));
}

void			check_tmp_env_helper(int i, int j, char *line, char **taab)
{
	int		hold;
	int		l;

	while (line[i] != '\0')
	{
		hold = i;
		i = next_separator_env(line, i, 0);
		if (!(taab[j] = ft_malloc(sizeof(char) * i + 1)))
			return ;
		l = 0;
		while (hold < i)
		{
			taab[j][l] = line[hold];
			l++;
			hold++;
		}
		taab[j][l] = '\0';
		j++;
	}
	taab[j] = NULL;
}

char			*check_tmp_env(char *line, int i, int count)
{
	char	**taab;

	i = 0;
	while (line[i])
	{
		i = next_separator_env(line, i, 0);
		count++;
		if (line[i])
			i++;
	}
	if (!(taab = ft_malloc(sizeof(char*) * (count + 2))))
		return (NULL);
	i = 0;
	check_tmp_env_helper(i, 0, line, taab);
	line = check_if_swap_env(taab, line, 0, 0);
	return (line);
}
