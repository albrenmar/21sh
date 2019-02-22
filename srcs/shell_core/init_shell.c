/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/19 08:36:58 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char        **init_envp(t_lstcontainer *env)
{
    int                i;
    char            **envp;
    t_list            *tmp;
    t_keyval        *buf;

    envp = NULL;
    if (env != NULL)
    {
        i = env->size(env) + 1;
        envp = malloc(sizeof(char *)* i + 1);
        i = 0;
        tmp = env->firstelement;
        while (tmp)
        {
            buf = tmp->content;
            envp[i] = ft_strnew(0);
            envp[i] = ft_strjoinfree(envp[i], buf->key, 1);
            envp[i] = ft_strjoinfree(envp[i], "=", 1);
            envp[i] = ft_strjoinfree(envp[i], buf->value, 1);
            tmp = tmp->next;
            i++;
        }
        envp[i] = NULL;
    }
   return (envp);
}

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

	if (!(mysh = malloc(sizeof(t_shell))))
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	g_tracking.fg = 0;
	g_tracking.bg = 0;
	g_tracking.lastplace = 0;
	g_tracking.jobs = NULL;
	g_tracking.lastreturn = 0;
	g_tracking.spid = 0;
	g_tracking.mysh = mysh;
	g_tracking.mysh->hist = NULL;
	g_tracking.mysh->alias_lst = NULL;
	init_alias();
	g_tracking.mysh->env = ft_env_to_lst(environ);
	g_tracking.envtab = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->exec = NULL;
	g_tracking.mysh->order = NULL;
	add_missing_string();
	hist_file_to_lst();
}
