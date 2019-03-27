/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/03/25 07:14:10 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

t_expand	*new_expand(int len)
{
	t_expand	*new_letter;

	new_letter = ft_memalloc(sizeof(t_expand));
	new_letter->ltr = '\0';
	new_letter->len = len;
	new_letter->idx = 0;
	new_letter->next = NULL;
	new_letter->prev = NULL;
	return (new_letter);
}

void		create_list_expand(t_expand *new_letter, char *line)
{
	int			i;
	int			len;
	t_expand	*frst_letter;
	t_expand	*prev_letter;

	i = 0;
	len = new_letter->len;
	frst_letter = new_letter;
	while (line && line[i])
	{
		new_letter->ltr = line[i];
		new_letter->idx = i + 1;
		if (line[i + 1])
		{
			prev_letter = new_letter;
			new_letter->next = new_expand(len);
			new_letter = new_letter->next;
			new_letter->prev = prev_letter;
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

void		scan_arg_transformer(t_unquoter **check, char **value)
{
	t_scan_arg	scarg;

	scarg.checker = *check;
	scarg.new_arg = NULL;
	while (scarg.checker && scarg.checker->str_unquoted)
	{
		if (scarg.checker->type != '\'')
			fill_scarg(&scarg);
		scarg.checker = scarg.checker->next;
	}
	scarg.checker = *check;
	ft_strdel(value);
	*value = ft_strnew(1);
	while (scarg.checker->str_unquoted)
	{
		*value = ft_strjoinfree(*value, scarg.checker->str_unquoted, 1);
		scarg.checker = scarg.checker->next;
	}
}

char		expand_transformer(char **value)
{
	char		*str_orig;
	t_unquoter	*to_unquot;
	t_unquoter	*first;

	to_unquot = NULL;
	to_unquot = unquote_value(value);
	first = to_unquot;
	str_orig = ft_strdup(*value);
	if (to_unquot && (!ft_strstr(to_unquot->str_unquoted, "${}")
			|| !ft_strstr(to_unquot->str_unquoted, "${}")))
		scan_arg_transformer(&to_unquot, value);
	else if ((to_unquot && ft_strequ(to_unquot->str_unquoted, "${}"))
			|| ft_strequ(str_orig, "${}")
			|| ft_strstr(to_unquot->str_unquoted, "${}"))
	{
		if (ft_strequ(to_unquot->str_unquoted, "${}"))
			print_exp_error(NULL);
		else
			print_exp_str_error(to_unquot->str_unquoted);
		ft_strdel(value);
		*value = ft_strdup(" ");
	}
	ft_strdel(&str_orig);
	clean_unquoter(first);
	return (0);
}
