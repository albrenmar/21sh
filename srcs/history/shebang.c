/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shebang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/02/18 17:10:33 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shebang_parse(t_core *core, char *word)
{
	if ()
}

void	shebang_word(t_core *core, char *word)
{
	while (core->hist->next)
		core->hist = core->hist->next;
	while (core->hist && ft_strncmp(word, core->hist->line, ft_strlen(word)))
	{
		if (core->hist->previous)
			core->hist = core->hist->next;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
}

void	shebang_number_pos(t_core *core, int num)
{
	char *tmp;

	tmp = NULL;
	while (core->hist->previous)
		core->hist = core->hist->previous;
	while (core->hist && core->hist->index > num)
	{
		if (core->hist->next)
			core->hist = core->hist->next;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
	if (core->hist && core->hist->index == num)
	{
		ft_putendl(core->hist->line);
		// Execution de la commande
		if ((tmp = test_command(core, 0)) != NULL)
			exec_cmd(core, tmp);
		else
		{
			ft_putstr_fd(NOT_FOUND, 2);
			ft_putendl_fd(core->arg[0], 2);
		}
		return ;
	}
	return ;
}

void	shebang_number_neg(t_core *core, int num)
{
	char *tmp;

	tmp = NULL;
	while (core->hist->next)
		core->hist = core->hist->next;
	while (core->hist && core->hist->index > num)
	{
		if (core->hist->previous)
			core->hist = core->hist->previous;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
	if (core->hist && core->hist->index == num)
	{
		return (core->hist->line);
	}
	return ;
}

// SHEBANG PAS ENCORE INCLUS A METTRE DANS HISTORY BUILTIN P