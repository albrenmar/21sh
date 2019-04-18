/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 03:24:47 by mjose             #+#    #+#             */
/*   Updated: 2019/04/13 05:38:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh21.h"

void	transform_if_tilde(t_expand **expand, char **str)
{
	t_expand	**first_letter;
	t_expand	*letter;

	first_letter = expand;
	letter = *expand;
	if (letter->ltr == '~' && !letter->next && !letter->prev)
	{
		expand_tilde_only(str);
		letter = *first_letter;
	}
	else if (letter->ltr == '~' && letter->next && !letter->prev)
	{
		if (letter->next->ltr == '/')
			expand_tilde_path(str);
		else if (letter->next->ltr && letter->next->ltr != '-'
				&& letter->next->ltr != '+' && letter->next->ltr != '~')
			expand_tilde_user(str);
		else if (letter->next->ltr && (letter->next->ltr == '-'
				|| letter->next->ltr == '+'))
			expand_tilde_pwd(str, first_letter);
	}
}

int		is_sysvar(char **str)
{
	char	*run_str;

	run_str = *str;
	if (!run_str || run_str[0] == 0)
		return (0);
	if (run_str[0] == '$' && run_str[1] == '$')
	{
		ft_strdel(str);
		*str = ft_itoa(getpid());
		return (1);
	}
	else if (run_str[0] == '$' && run_str[1] == '?')
	{
		ft_strdel(str);
		*str = ft_itoa(g_tracking.expandreturn);
		return (1);
	}
	return (0);
}

int		transform_simple(char **str)
{
	char	*run_str;
	char	*new_str;

	run_str = *str;
	new_str = NULL;
	if (run_str[0] == '$')
		new_str = ft_strdup(get_env_string(run_str + 1));
	if (run_str[0] == '$' && !new_str)
		new_str = ft_strdup(get_parm_string(run_str + 1));
	if (new_str)
	{
		ft_strdel(str);
		*str = new_str;
	}
	else if (*str && is_sysvar(str))
		return (0);
	else if (run_str[0] == '$' && run_str[1])
	{
		ft_strdel(str);
		*str = ft_strdup(" ");
		g_tracking.mysh->err_expend = 1;
		return (1);
	}
	return (0);
}

void	transform(t_expand *expand, char **str)
{
	t_expand	*first_letter;
	char		*tmp;

	first_letter = expand;
	tmp = *str;
	transform_if_tilde(&first_letter, str);
	while (expand->ltr && expand->ltr != '~')
	{
		if (expand->ltr == '$' && expand->next && expand->next->ltr != '?')
		{
			first_letter = expand_keys(expand, str);
			expand = first_letter;
		}
		if (expand->next && !g_tracking.mysh->err_expend)
			expand = expand->next;
		else
			break ;
	}
	if (!g_tracking.mysh->err_expend && *str && transform_simple(str))
		delete_list_expand(&first_letter);
}
