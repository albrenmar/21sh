/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:43 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:31:39 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*ft_create_elem(t_env *lst, char *name, char *value)
{
	t_env	*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp->name = ft_strdup(name);
	tmp->value = ft_strdup(value);
	tmp->next = lst;
	return (tmp);
}

t_env		*pushback(t_env *lst, char *name, char *value, char *env)
{
	t_env	*tmp;
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->name = (name) ? ft_strdup(name) : ft_strdup("");
	new->value = (value) ? ft_strdup(value) : ft_strdup("");
	new->env = ft_strdup(env);
	new->next = NULL;
	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}
