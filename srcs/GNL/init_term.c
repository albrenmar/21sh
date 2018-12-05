/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:29:52 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/05 15:13:34 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		yan_putchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void	init_key_list()
{
	char	*tmp;

	g_tracking.key_list = lstcontainer_new();
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LEFT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_RIGHT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DOWN));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LUP));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_LDOWN));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_WLEFT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_WRIGHT));
	lstcontainer_add(g_tracking.key_list, ft_strdup(K_DEL));
}

void	cursor_reset(void)
{
	g_tracking.pos->abs = 0;
	g_tracking.pos->x = 1;
	g_tracking.pos->y = 0;
	g_tracking.pos->relx = 1;
	g_tracking.pos->rely = 0;
	g_tracking.pos->legacy = 0;
	g_tracking.swi = 0;
}

void	cursorinit(void)
{
	if ((g_tracking.pos = malloc(sizeof(t_cursor) + 1)) == NULL)
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	cursor_reset();
	init_key_list();
}
