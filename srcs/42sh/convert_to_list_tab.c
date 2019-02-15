/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_list_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 07:07:00 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/07 02:47:59 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

void	add_word(char **temp, char *name)
{
	char	*cmd;

	if (temp == NULL)
		*temp = ft_strdup("");
	cmd = *temp;
	*temp = ft_strjoin(cmd, " ");
	cmd = *temp;
	*temp = ft_strjoin(cmd, name);
}

t_tab_arg		*new_tab_list(int option)
{
	t_tab_arg	*tab;

	tab = ft_memalloc(sizeof(t_tab_arg));
	tab->next = NULL;
	tab->prev = NULL;
	if (option == 1)
	{
		tab->tab_test = NULL;
	}
	else
	{
		tab->tab_test = ft_memalloc(sizeof(char *) * 2);
		tab->tab_test[1] = NULL;
	}
	return (tab);
}

t_tab_arg	*convert_to_list_tab(t_last	*list)
{
	t_tab_arg	*tab;
	t_tab_arg	*temp_tab;
	char		*temp;
	int			i;

	temp = NULL;
	tab = NULL;
	if (list->type == OP || list->type == PA)
	{
		tab = new_tab_list(0);
		temp_tab = tab;
		tab->tab_test[0] = ft_strdup(list->name);
		tab->type = list->type;
	}
	else
	{
		add_word(&temp, list->name);
	}
	if ((list->type != OP && list->type != PA) && (!list->next || (list->next && (list->next->type == OP || list->next->type == PA))))
	{
		tab = new_tab_list(1);
		temp_tab = tab;
		tab->tab_test = ft_strsplit(temp, ' ');
		tab->type = list->type;
		temp = NULL;
	}
	list = list->next;
	while (list)
	{
		if (list->type == OP || list->type == PA)
		{
			tab->next = new_tab_list(0);
			tab->next->prev = tab;
			tab = tab->next;
			tab->tab_test[0] = ft_strdup(list->name);
			tab->type = list->type;
			list = list->next;
		}
		else
		{
			while (list && (list->type != OP && list->type != PA))
			{
				add_word(&temp, list->name);
				list = list->next;
			}
			if (!tab)
			{
				tab = new_tab_list(1);
				temp_tab = tab;
				tab->tab_test = ft_strsplit(temp, ' ');
				tab->type = CMD;
				temp = NULL;
			}
			else
			{
				tab->next = new_tab_list(1);
				tab->next->prev = tab;
				tab = tab->next;
				tab->tab_test = ft_strsplit(temp, ' ');
				tab->type = CMD;
				temp = NULL;
			}
		}
	}
	/*while (temp_tab)
	{
		i = 0;
		printf("CMD = ");
		while (temp_tab->tab_test[i])
		{
			printf("%s   ", temp_tab->tab_test[i]);
			i++;
		}
		printf("\n");
		temp_tab = temp_tab->next;
	}*/
	return (temp_tab);
}
