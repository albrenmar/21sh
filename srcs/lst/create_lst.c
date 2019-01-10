/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:33 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:27:33 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_core		*create_core_struct(void)
{
	t_core	*core;

	if (!(core = (t_core *)malloc(sizeof(t_core))))
		return (NULL);
	return (core);
}

t_env		*create_lst(void)
{
	t_env	*lst;

	lst = NULL;
	return (lst);
}
