/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:29:52 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/01 03:35:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		yan_putchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void	init_key_list(void)
{
	char	*tmp;

	g_tracking.key_list = lstcontainer_new();
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LEFT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_RIGHT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DOWN));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_UP));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DEL));
}

void	cursorinit(void)
{
	if ((g_tracking.pos = malloc(sizeof(t_cursor) + 1)) == NULL)
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	g_tracking.pos->abs = 0;
	g_tracking.pos->x = 1;
	g_tracking.pos->y = 0;
	g_tracking.pos->relx = 1;
	g_tracking.pos->rely = 0;
	g_tracking.pos->prompt = 1;
	g_tracking.pos->legacy = 0;
	g_tracking.swi = 0;
	init_key_list();
}
