/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 01:29:12 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/30 02:51:02 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	print_list2(t_lstcontainer *list)
{
	t_list		*buf;
	char		*tmp;

	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		ft_putendl(tmp);
		buf = buf->next;
	}
}

void	print_list_rev(t_lstcontainer *list)
{
	t_list		*buf;
	char		*tmp;

	buf = ft_lstgetlast(list->firstelement);
	while (buf)
	{
		tmp = buf->content;
		ft_putendl(tmp);
		buf = buf->prev;
	}
}

void	rm_pointer(t_list *to_rm)
{
	t_list		*prev;
	t_list		*next;

	prev = to_rm->prev;
	next = to_rm->next;

	prev->next = next;
	next->prev = prev;
}

void	add_pointer(t_list	*ref, t_list *to_add)
{
	t_list		*prev;
	t_list		*next;

	prev = ref->prev;
	if (prev)
		prev->next = to_add;
	to_add->prev = prev;
	to_add->next = ref;
	ref->prev = to_add;
}

void	insert_node(t_list *ref_node, t_list *insert)
{
	t_list	*tmp;

	tmp = insert;
	rm_pointer(insert);
	add_pointer(ref_node, insert);
}

int		main(int argc, char **argv)
{
	char			*tmp;
	int				i;
	t_lstcontainer	*new;
	t_list			*insert;

	i = 0;
	tmp = ft_itoa(i);
	new = lstcontainer_new();
	while (i < 10)
	{
		tmp = ft_itoa(i);
		lstcontainer_add(new, tmp);
		i++;
	}
	print_list2(new);
	i = 0;
	insert = new->firstelement;
	while (i < 6)
	{
		insert = insert->next;
		i++;
	}
	insert_node(new->firstelement, insert);
	ft_putchar('\n');
	print_list2(new);
	ft_putchar('\n');
	print_list_rev(new);
	return (0);
}