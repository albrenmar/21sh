/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/01/29 07:09:26 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

t_expand	*new_expand(void)
{
	t_expand	*new_letter;

	new_letter = ft_memalloc(sizeof(t_expand));
	new_letter->ltr = '\0';
	new_letter->next = NULL;
	return (new_letter);
}

void		create_list_expand(t_expand *new_letter, char *line)
{
	int			i;
	t_expand	*frst_letter;

	i = 0;
	frst_letter = new_letter;
	while (line[i])
	{
		new_letter->ltr = line[i];
		if (line[i + 1] && !ft_iswhitespace(line[i]))
		{
			new_letter->next = new_expand();
			new_letter = new_letter->next;
			i++;
		}
		else
			break ;
	}
	new_letter = frst_letter;
}

int			need_expand(char *to_transf)
{
	if (to_transf[0] == '~' && !to_transf[1])
		return (1);
	else if (to_transf[0] && to_transf[1] == '/')
		return (1);
	else if (to_transf[0] == '~' && (to_transf[1] == '+'
			|| to_transf[1] == '-') && (!to_transf[2]
			|| to_transf[2] == '/'))
		return (1);
	else if (to_transf[0] == '~' && have_homedir(to_transf))
		return (1);
	else if (have_parm(to_transf))
		return (1);
	return (0);
}

void		expand_transformer(char *line, t_env *env)
{
	char		*to_transf;
	t_expand	*expand;

	to_transf = line;
	expand = NULL;
	if (need_expand(to_transf))
	{
		expand = new_expand();
		create_list_expand(expand, to_transf);
//		tilde_transformer(expand, env);
	}
}
