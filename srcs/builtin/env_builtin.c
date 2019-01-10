/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:26:38 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:30:15 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env			*ft_unsetenv(t_core *core, char *name)
{
	t_env		*lst;

	lst = ft_delete(core->env, name);
	return (lst);
}

static void		ft_setifempty(t_core *core, char *tenv, char *name, char *value)
{
	t_env		*tmp;

	tmp = core->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tenv = ft_strjoin(name, "=");
			free(tmp->env);
			free(tmp->name);
			free(tmp->value);
			tmp->name = name;
			tmp->value = value;
			tmp->env = ft_strjoinfree(tenv, value, 1);
		}
		tmp = tmp->next;
	}
}

bool			ft_setenv(t_core *core, char *name, char *value)
{
	char		*tenv;

	tenv = NULL;
	if (ft_count_list(core->env) > 0 && ft_envexist(name, core->env))
		ft_setifempty(core, tenv, name, value);
	else
	{
		tenv = ft_strjoin(name, "=");
		tenv = ft_strjoinfree(tenv, value, 1);
		core->env = pushback(core->env, name, value, tenv);
		free(tenv);
		free(name);
		free(value);
	}
	return (TRUE);
}

char			**ft_env_to_tab(t_core *core)
{
	t_env		*lst;
	char		*tenv;
	char		**env;
	int			i;

	i = 0;
	lst = core->env;
	if (!(env = (char **)malloc(sizeof(char *) * (ft_count_list(lst) + 1))))
		return (NULL);
	while (lst)
	{
		tenv = ft_strjoin(lst->name, "=");
		env[i] = (lst->value) ? ft_strjoin(tenv, lst->value) \
				: ft_strjoin(tenv, "");
		lst = lst->next;
		if (tenv)
			free(tenv);
		i++;
	}
	env[i] = NULL;
	return (env);
}
