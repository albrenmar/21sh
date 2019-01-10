/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:27:13 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:27:13 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		ft_free_tab(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void		ft_free_struct(t_core *core)
{
	ft_free_tab(core->arg);
	ft_free_tab(core->path);
	(core->line) ? free(core->line) : 0;
	free(core);
}

void		free_link(t_env *tmp)
{
	free(tmp->name);
	free(tmp->value);
	free(tmp->env);
	free(tmp);
}

void		ft_free_list(t_env *env)
{
	t_env	*begin;

	while (env)
	{
		begin = env;
		free(env->name);
		free(env->value);
		free(env->env);
		env = env->next;
		free(begin);
	}
	free(env);
}
