/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by alsomvil          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/04 14:56:35 by mjose            ###   ########.fr       */
=======
/*   Updated: 2019/02/25 06:14:30 by mjose            ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	char		**tab_exec;
	int			i;
	int			j;

	begin = list;
	i = 0;
	i++;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	list = begin;
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	tab_exec[i] = list->name;
<<<<<<< HEAD
	expand_transformer(&tab_exec[i], 1); // Modifie par MJOSE :: a parler avec Alsomvil
=======
	expand_transformer(&tab_exec[i]);
>>>>>>> alsomvil
	list = list->next;
	i++;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
		{
			tab_exec[i] = list->name;
<<<<<<< HEAD
			if (expand_transformer(&tab_exec[i], 1) == 'E' // Modifie par MJOSE :: a parler avec Alsomvil// Modifie par MJOSE :: a parler avec Alsomvil
				|| g_tracking.mysh->expand_error) // Modifie par MJOSE :: a parler avec Alsomvil
			{ // Modifie par MJOSE :: a parler avec Alsomvil
				rmv_tab_exec(&tab_exec[i], i); // Modifie par MJOSE :: a parler avec Alsomvil
				tab_exec = NULL; // Modifie par MJOSE :: a parler avec Alsomvil
				break ; // Modifie par MJOSE :: a parler avec Alsomvil
			} // Modifie par MJOSE :: a parler avec Alsomvil
			i++;
			tab_exec[i] = NULL; // Modifie par MJOSE :: a parler avec Alsomvil
		}
		list = list->next;
	}
//	tab_exec[i] = NULL;
	if (tab_exec)
		tab_exec[i] = NULL;
=======
			expand_transformer(&tab_exec[i]);
			i++;
		}
		list = list->next;
	}
	tab_exec[i] = NULL;
>>>>>>> alsomvil
	/*i = 0;
	while (tab_exec[i])
	{
		printf("TAB[%d] = %s\n", i, tab_exec[i]);
		i++;
	}*/
	//exit (0);
	return (tab_exec);
}
