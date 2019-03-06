/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/05 23:47:10 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void			clean_tab_exec(char **tab_exec)
{
	int			i;

	while (tab_exec[i] != '\0')
	{
		if (ft_strlen(tab_exec[i]) == 0)
		{
			ft_strdel(&tab_exec[i]);
			tab_exec[i] = NULL;
		}
		i++;
	}
}

int				spaces_line_check(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t' && line[i] != '\v'
		&& line[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

void			transform_cwd(void)
{
	char		*home;
	int			len;
	char		*newcwd;
	int			i;

	home = ft_strdup(get_env_string("HOME"));
	if (ft_strstr(g_tracking.cwd, home))
	{
		len = ft_strlen(home);
		if (!(newcwd = malloc(sizeof(char) * ft_strlen(g_tracking.cwd) - len + 2)))
			return ;
		i = 0;
		len = len + 2;
		newcwd[i++] = '<';
		newcwd[i++] = ' ';
		newcwd[i++] = '~';
		while (g_tracking.cwd[len] != '\0')
		{
			newcwd[i] = g_tracking.cwd[len];
			len++;
			i++;
		}
		newcwd[i] = '\0';
		ft_strdel(&g_tracking.cwd);
		g_tracking.cwd = newcwd;
	}
}

void			print_prompt(void)
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 2);
	ft_putstr_fd(g_tracking.user, 2);
	ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
	ft_putchar_fd(' ', 2);
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
	
	g_tracking.user = ft_strdup("[");
	memory = g_tracking.user;
	g_tracking.user = ft_strjoin(g_tracking.user, getlogin());
	ft_strdel(&memory);
	memory = g_tracking.user;
	g_tracking.user = ft_strjoin(g_tracking.user, "]");
	ft_strdel(&memory);
	g_tracking.cwd = ft_strdup("< ");
	memory = g_tracking.cwd;
	getcwd(buff, 4096 + 1);
	g_tracking.cwd = ft_strjoin(g_tracking.cwd, buff);
	ft_strdel(&memory);
	memory = g_tracking.cwd;
	g_tracking.cwd = ft_strjoin(g_tracking.cwd, " >");
	ft_strdel(&memory);
	transform_cwd();
	prompt = ft_strdup(SHELL_NAME);
	memory = prompt;
	prompt = ft_strjoin(prompt, " $/> ");
	ft_strdel(&memory);
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = utf_strlen(prompt) + utf_strlen(g_tracking.cwd);
	g_tracking.pos->prompt += utf_strlen(g_tracking.user);
	g_tracking.pos->prompt +=2;
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
