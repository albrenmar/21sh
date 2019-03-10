/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:55:04 by mjose             #+#    #+#             */
/*   Updated: 2019/03/10 14:58:54 by mjose            ###   ########.fr       */
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

int			scan_arg_transformer(char **arg, char quote)
{
	t_expand	*expand;
	t_scan		*scan;
	t_scan		*first_scan;
	char		*new_arg;

	scan = new_scan();
	first_scan = scan;
	scan_argument(*arg, scan, 0, quote);
	new_arg = NULL;
	while (scan && scan->sstring)
	{
		expand = new_expand(ft_strlen(scan->sstring));
		create_list_expand(expand, scan->sstring);
		if ((scan->sstring[0] != '~' && !quote) || scan->sstring[0] == '$')
			if (transform(expand, &scan->sstring))
				return (1);
		if (!new_arg)
			new_arg = ft_strnew(1);
		new_arg = ft_strjoinfree(new_arg, scan->sstring, 1);
		scan = scan->next;
	}
	scan = first_scan;
	ft_strdel(arg);
	*arg = new_arg;
	return (0);
}

char		expand_transformer(char **value, int chg_value)
{
	char	quote;
	char	*str_error;

	quote = 0;
	str_error = ft_strdup(*value);
	if (chg_value)
		quote = unquote_value(value, quote);
	if (quote != '\'' && quote != 'E' && *value)
		quote = scan_arg_transformer(value, quote);
	else if (quote == 'E')
	{
		print_exp_error(str_error);
		ft_strdel(value);
		*value = ft_strdup("");
	}
	if (quote == 1)
		*value = ft_strdup("");
	ft_strdel(&str_error);
	return (quote);
}
