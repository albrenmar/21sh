/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/03 07:42:22 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void			print_prompt(void)
{
	ft_putstr_fd(ANSI_COLOR_MAGENTA, 2);
	ft_putstr_fd(g_tracking.cwd, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(ANSI_COLOR_GREEN, 2);
	ft_putstr_fd(g_tracking.prompt, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
}

void			get_coolprompt(void)
{
	char	*prompt;
	char	*memory;
	char	buff[4096 + 1];

	g_tracking.cwd = ft_strdup("<");
	memory = g_tracking.cwd;
	getcwd(buff, 4096 + 1);
	g_tracking.cwd = ft_strjoin(g_tracking.cwd, buff);
	ft_strdel(&memory);
	g_tracking.cwd = ft_strjoin(g_tracking.cwd, ">");
	prompt = ft_strdup(SHELL_NAME);
	memory = prompt;
	prompt = ft_strjoin(prompt, " $> ");
	ft_strdel(&memory);
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = ft_strlen(prompt);
	ft_strdel(&prompt);
}

char			**tab_dup(char **tob)
{
	int			i;
	char		**new;

	i = 0;
	while (tob[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
			return (NULL);
	i = 0;
	while (tob[i])
	{
		new[i] = ft_strdup(tob[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}