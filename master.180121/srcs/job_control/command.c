/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:20:22 by mjose             #+#    #+#             */
/*   Updated: 2019/01/26 06:29:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh42.h"
#include "minishell.h"
#include "job_control.h"

char	*command_wout_sym(char *cmd)
{
	char	*cmd_sub;
	char	*cmd_trim;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|' || cmd[i] == '&')
			break ;
		i++;
	}
	cmd_sub = ft_strsub(cmd, 0, i, 0);
	cmd_trim = ft_strtrim(cmd_sub);
	ft_strdel(&cmd_sub);
	return (cmd_trim);
}
