/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/30 06:16:26 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#define PA 1
#define OP 2
#define CMD 3
#define ARG 4
#define OPT 5
#define PATH 6


char	*check_quote(char *line, int *i, int *nb)
{
	printf("%s\n", "modification de la commande sans quote");
	exit (0);
	return (line);
}

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;

	test = NULL;
	if (!line[nb])
		return (NULL);
	if (line[nb] == '\'' || line[nb] == '\"')
		return (check_quote(line, i, &nb));
	while (line[nb])
	{
		if (line[nb] == ';' || line[nb] == '|' || line[nb] == '&' || line[nb] == '>' || line[nb] == '<' || line[nb] == '(' || line[nb] == ')')
		{
			if (line[nb + 1] && (line[nb + 1] == line[nb]))
			{
				test = ft_strndup(line, 2);
				(*i) = (*i) + 2;
				nb = nb + 2;
			}
			else
			{
				test = ft_strndup(line, 1);
				(*i) = (*i) + 1;
				nb = nb + 1;
			}
		}
		else
		{
			while (line[nb] && line[nb] != ' ' && line[nb] != ';' && line[nb] != '|' && line[nb] != '&' && line[nb] != '>' && line[nb] != '<' && line[nb] != '(' && line[nb] != ')')
			{
				nb++;
				(*i)++;
			}
			test = ft_strndup(line, nb);
		}
		while (line[nb++] == ' ')
			(*i)++;
		return (test);
	}
	return (test);
}

t_last	*create_new_list(void)
{
	t_last	*list;

	list = malloc(sizeof(t_last));
	list->name = NULL;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	ft_analize_arg(t_last *list_cmd)
{
	while (list_cmd->next)
	{
		if (list_cmd->name[0] == '(' || list_cmd->name[0] == ')')
		{
			list_cmd->type = PA;
			list_cmd = list_cmd->next;
		}
		else if (list_cmd->name[0] == ';' || list_cmd->name[0] == '|' || list_cmd->name[0] == '>' || list_cmd->name[0] == '<' || list_cmd->name[0] == '&')
		{
			list_cmd->type = OP;
			list_cmd = list_cmd->next;
		}
		else if (!list_cmd->prev || (list_cmd->prev && (list_cmd->prev->type == OP || list_cmd->prev->type == PA)))
		{
			list_cmd->type = CMD;
			list_cmd = list_cmd->next;
		}
		else if (list_cmd->prev && list_cmd->prev->type == CMD && list_cmd->name[0] == '-')
		{
			list_cmd->type = OPT;
			list_cmd = list_cmd->next;
		}
		else
		{
			list_cmd->type = ARG;
			list_cmd = list_cmd->next;
		}
	}
}

int		error_lexer(t_last *list_cmd)
{
	while (list_cmd->next)
	{
		if (list_cmd->type == OP && list_cmd->next->type == OP)
		{
			if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == ';')
			{
				if (list_cmd->next->next && (((ft_strlen(list_cmd->next->name) == 1) && ft_strlen(list_cmd->next->next->name) == 2)
							|| ((ft_strlen(list_cmd->next->name) == 2) && (list_cmd->next->next && list_cmd->next->next->type == OP))))
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (ft_strlen(list_cmd->name) == 1 && list_cmd->name[0] == '>')
			{
				if (ft_strlen(list_cmd->next->name) == 2 || list_cmd->next->name[0]== ';' || (list_cmd->next->next && list_cmd->next->next->type == OP))
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] == ';')
			{
				printf("Error\n");
				return (1);
			}
			else if (ft_strlen(list_cmd->name) == 2 || ft_strlen(list_cmd->next->name) == 2)
			{
				if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] == '|' && list_cmd->next->next && list_cmd->next->next->type == OP)
				{
					printf("Error\n");
					return (1);
				}
				else if (ft_strlen(list_cmd->name) == 2 && list_cmd->name[0] != '|')
				{
					printf("Error\n");
					return (1);
				}
			}
			else if (list_cmd->next->next && (list_cmd->next->next->type == OP))
			{
				printf("Error\n");
				return (1);
			}
		}
		list_cmd = list_cmd->next;
	}
	return (0);
}

void	rm_pointer(t_last *to_rm)
{
	t_last		*prev;
	t_last		*next;

	prev = to_rm->prev;
	next = to_rm->next;

	prev->next = next;
	next->prev = prev;
}

void	add_pointer(t_last	*ref, t_last *to_add)
{
	t_last		*prev;
	t_last		*next;

	prev = ref->prev;
	if (prev)
		prev->next = to_add;
	to_add->prev = prev;
	ref->prev = to_add;
	to_add->next = ref;
}

void	insert_node(t_last *ref_node, t_last *insert)
{
	t_last	*tmp;

	printf("node 1 = %s node 2 = %s\n", ref_node->name, insert->name);
	tmp = insert;
	rm_pointer(insert);
	add_pointer(ref_node, insert);
}

void	tri_lexer(t_last *list_cmd)
{
	t_last	*temp;
	t_last	*temp_pipe;

	temp = list_cmd;
	while (list_cmd && list_cmd->next)
	{
		if (list_cmd->type == OP && list_cmd->name[0] == '>')
		{
			if (list_cmd->next->type == OP && (list_cmd->next->name[0] == '|') && ft_strlen(list_cmd->next->name) ==  1)
				temp_pipe = list_cmd->next->next->next;
			else
				temp_pipe = list_cmd->next->next;
			if (temp_pipe && (temp_pipe->type == ARG || temp_pipe->type == OPT))
			{
				insert_node(list_cmd, temp_pipe);
				list_cmd = temp;
			}
			else
				list_cmd = list_cmd->next;
		}
		else
			list_cmd = list_cmd->next;
	}
}


t_last	*ft_analize(char *line)
{
	char	*temp;
	int		i;
	t_last	*list_cmd;
	t_last	*templist;

	i = 0;
	temp = NULL;
	list_cmd = create_new_list();
	templist = list_cmd;
	while (line[i] == ' ')
		i++;
	while ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		list_cmd->name = ft_strdup(temp);
		free(temp);
		list_cmd->next = ft_memalloc(sizeof(t_last));
		list_cmd->next->prev = list_cmd;
		list_cmd = list_cmd->next;
	}
	list_cmd = NULL;
	ft_analize_arg(templist);
	if (error_lexer(templist))
		return (NULL);
	if (templist)
		tri_lexer(templist);
	while (templist->prev)
		templist = templist->prev;
	//templist = templist->prev;
/*	while (templist && templist->next)
	{
		printf("ARG = %s TYPE = %d\n", templist->name, templist->type);
		templist = templist->next;
	}
*/	return (templist);
}
