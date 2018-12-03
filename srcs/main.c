/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:12:58 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/03 00:51:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		main(void)
{
	char	*prompt;
	char	*cmd;
	int		i;

	cursorinit();
	prompt = ft_strdup("Fake minishell >");
	g_tracking.prompt = ft_strdup(prompt);
	g_tracking.pos->prompt = ft_strlen(prompt);
	ft_siginit();
	get_term();
	while (get_key() > 0)
	{
		cmd = ft_strdup(g_tracking.cmd);
		ft_putchar('\n');
		ft_putstr("Execution de la commande");
		ft_putchar('"');
		ft_putstr(cmd);
		ft_putchar('"');
		g_tracking.swi = 0;
		ft_putchar('\n');
	}
	return (0);
}
