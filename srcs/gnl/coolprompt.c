/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coolprompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/27 06:21:12 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	transform_cwd(int i)
{
	char		*home;
	int			len;
	char		*n;

	home = ft_strdup(get_env_string("HOME"));
	if (ft_strstr(g_tracking.cwd, home))
	{
		len = ft_strlen(home);
		if (!(n = malloc(sizeof(char) * ft_strlen(g_tracking.cwd) - len + 2)))
			return ;
		len = len + 2;
		n[i++] = '<';
		n[i++] = ' ';
		n[i++] = '~';
		while (g_tracking.cwd[len] != '\0')
		{
			n[i++] = g_tracking.cwd[len];
			len++;
		}
		n[i] = '\0';
		ft_strdel(&g_tracking.cwd);
		g_tracking.cwd = n;
	}
	free(home);
}

void	set_prompt_quote(void)
{
	if (g_tracking.quotes == 1)
		g_tracking.prompt = ft_strdup("dquotes >");
	if (g_tracking.quotes == 2)
		g_tracking.prompt = ft_strdup("quotes >");
	if (g_tracking.quotes == 3)
		g_tracking.prompt = ft_strdup(">");
	g_tracking.pos->prompt = utf_strlen(g_tracking.prompt);
}

void	print_prompt(void)
{
	if (g_tracking.quotes == 1
			|| g_tracking.quotes == 2 || g_tracking.quotes == 3)
	{
		ft_putstr_fd(ANSI_COLOR_RED, 2);
		ft_putstr_fd(g_tracking.prompt, 2);
		ft_putstr_fd(ANSI_COLOR_DEFAULT, 2);
		return ;
	}
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

void	get_coolprompt_cont(int mode, char *memory, char *prompt)
{
	int	i;

	i = 0;
	if (mode == 1)
		g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, "No environment", 1);
	g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, " >", 1);
	if (get_env_string("HOME"))
		transform_cwd(i);
	prompt = ft_strdup(SHELL_NAME);
	prompt = ft_strjoinfree(prompt, " $/> ", 1);
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = utf_strlen(prompt) + utf_strlen(g_tracking.cwd);
	g_tracking.pos->prompt += utf_strlen(g_tracking.user);
	g_tracking.pos->prompt += 2;
	ft_strdel(&prompt);
}

void	get_coolprompt(void)
{
	char	*prompt;
	char	*memory;
	char	buff[4096 + 1];

	memory = NULL;
	prompt = NULL;
	ft_strdel(&g_tracking.prompt);
	ft_strdel(&g_tracking.cwd);
	ft_strdel(&g_tracking.user);
	if (g_tracking.quotes >= 1 && g_tracking.quotes <= 3)
		return (set_prompt_quote());
	g_tracking.user = ft_strdup("[");
	g_tracking.user = ft_strjoinfree(g_tracking.user, getlogin(), 1);
	g_tracking.user = ft_strjoinfree(g_tracking.user, "]", 1);
	g_tracking.cwd = ft_strdup("< ");
	if (get_env_string("HOME"))
	{
		getcwd(buff, 4096 + 1);
		g_tracking.cwd = ft_strjoinfree(g_tracking.cwd, buff, 1);
		return (get_coolprompt_cont(2, memory, prompt));
	}
	return (get_coolprompt_cont(1, memory, prompt));
}
