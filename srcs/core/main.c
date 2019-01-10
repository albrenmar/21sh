/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:19 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/19 11:04:23 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_display_prompt(int putendl)
{
	char	buff[PATH_MAX + 1];
	char	*cw;
	char	*prompt;

	if (!(cw = getcwd(buff, PATH_MAX)))
		prompt = "my shell";
	ft_putchar('[');
	(cw) ? ft_putcolor(RED, cw) : ft_putcolor(RED, prompt);
	ft_putchar(']');
	ft_putstr(" $> ");
	if (putendl)
		ft_putchar('\n');
}

int			main(int argc, char **argv, char **env)
{
	minishell(argc, argv, env);
	return (0);
}
