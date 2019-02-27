/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/17 09:16:04 by mjose            ###   ########.fr       */
=======
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/25 13:58:32 by abe              ###   ########.fr       */
>>>>>>> mjose.merge
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_printlist(void)
{
	t_list			*tmp;
	t_keyval		*buf;

	tmp = g_tracking.mysh->env->firstelement;
	buf = NULL;
	while (tmp)
	{
		buf = tmp->content;
		ft_putstr(buf->key);
		ft_putchar('=');
		ft_putendl(buf->value);
		tmp = tmp->next;
	}
}

void	init_shell(char **environ)
{
	t_shell		*mysh;
<<<<<<< HEAD

=======
	int			i;

	i = 0;
>>>>>>> mjose.merge
	if (!(mysh = malloc(sizeof(t_shell))))
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
<<<<<<< HEAD
=======
	while (i < 27)
	{
		g_tracking.hashtable[i] = NULL;
		i++;
	}
	g_tracking.builtin = 0;
	g_tracking.jobs = NULL;
	g_tracking.lastreturn = 0;
>>>>>>> mjose.merge
	g_tracking.mysh = mysh;
	g_tracking.mysh->hist = NULL;
	g_tracking.mysh->alias_lst = NULL;
	init_alias();
	g_tracking.mysh->env = ft_env_to_lst(environ);
<<<<<<< HEAD
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->exec = NULL;
	g_tracking.mysh->order = NULL;
	g_tracking.mysh->setenv_lst = NULL;
	add_missing_string();
	hist_file_to_lst();
=======
	add_missing_string();
	hist_file_to_lst();
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->setenv_lst = NULL;
>>>>>>> mjose.merge
}
