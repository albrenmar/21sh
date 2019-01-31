/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/01/31 01:19:05 by mjose            ###   ########.fr       */
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
		if (line[i + 1])
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
	else if (is_path_tilde(to_transf))
		return (1);
	else if (to_transf[0] == '~' && have_homedir(to_transf))
		return (1);
	else if (have_parm(to_transf))
		return (1);
	else if (is_to_add_or_mod_parm(to_transf))
		return (1);
	else if (to_transf[0] == '$' && to_transf[1])
		return (1);
	return (0);
}

void		expand_transformer(t_last *cmd)
{
	t_expand	*expand;
	t_last		*frst_cmd;

	expand = NULL;
	frst_cmd = cmd;
	while (cmd && cmd->name)
	{
		if (need_expand(cmd->name))
		{
			expand = new_expand();
			create_list_expand(expand, cmd->name);
			transform(expand, &cmd->name);
		}
		ft_putendl(cmd->name);
		if (cmd->next)
			cmd = cmd->next;
	}
	cmd = frst_cmd;
}
