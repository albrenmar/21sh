/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/10 16:16:56 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

static void		env_alloc_value(char *envp, char **value)
{
	int		i;
	int		len;
	int		hold;
	char	*tmp;

	i = 0;
	len = 0;
	while (envp[i] != '=')
		i++;
	i++;
	hold = i - 1;
	while (envp[i] != '\0')
	{
		i++;
		len++;
	}
	*value = (char*)malloc(sizeof(char) * len + 1);
	if (*value == NULL)
		return ;
	tmp = *value;
	i = 0;
	while (envp[hold++] != '\0')
		tmp[i++] = envp[hold];
	i--;
	tmp[i] = '\0';
}

static void		env_alloc_key(char *envp, char **key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] != '=')
		i++;
	*key = (char*)malloc(sizeof(char) * i + 1);
	if (*key == NULL)
		return ;
	tmp = *key;
	i = 0;
	while (envp[i] != '=')
	{
		tmp[i] = envp[i];
		i++;
	}
	tmp[i] = '\0';
}

static void		env_alloc(char **envp, t_env **env, int i, t_env *tmp)
{
	while (envp[i])
	{
		if (tmp == NULL)
		{
			if (!(*env = malloc(sizeof(t_env))))
				return ;
			if (i == 0)
				tmp = *env;
			env_alloc_key(envp[i], &tmp->key);
			env_alloc_value(envp[i], &tmp->value);
		}
		else
		{
			if (!(tmp->next = malloc(sizeof(t_env))))
				return ;
			tmp = tmp->next;
			env_alloc_key(envp[i], &tmp->key);
			env_alloc_value(envp[i], &tmp->value);
		}
		i++;
	}
	tmp->next = NULL;
}

void		env_format(char **envp, t_env **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	env_alloc(envp, env, i, tmp);
}