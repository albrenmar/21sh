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

char	*shebang_find(char *word)
{

	if (ft_strchr(word, '!'))
		return ft_strchr(word, '!');
	return 0;
}

void	shebang_parse(t_hist *hist, char *word)
{
	char num[50];
	int i;
	int j;

	i = 2;
	j = 0;
	if (!word[0] || word[0] != '!')
		return ;
	if (word[1] && ft_isalpha(word[1]))
		shebang_word(word);
	if ((word[1] && word[2]) && word[1] == '-' && ft_isdigit(word[2]))
	{
		while (ft_isdigit(word[i]))
		{
			if (i > 35)
				return (ft_putendl_fd("Event not found", 2));
			num[j++] = word[i++];
		}
		shebang_number_neg()
	}
	else if (word[1] && ft_isdigit(word[1]))
	{
		while (ft_isdigit(word[i]))
		{
			if (i > 35)
				return (ft_putendl_fd("Event not found", 2));
			num[j++] = word[i++];
		}
	}
}

void	shebang_word(t_hist *hist, char *word)
{
	while (hist->next)
		hist = hist->next;
	while (hist && ft_strncmp(word, hist->line, ft_strlen(word)))
	{
		if (hist->previous)
			hist = hist->next;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
}

void	shebang_number_pos(t_hist *hist, int num)
{
	char *tmp;

	tmp = NULL;
	while (hist->previous)
		hist = hist->previous;
	while (hist && hist->index > num)
	{
		if (hist->next)
			hist = hist->next;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
	if (hist && hist->index == num)
	{
		ft_putendl(hist->line);
		// Execution de la commande
		if ((tmp = test_command(core, 0)) != NULL)
			exec_cmd(core, tmp);
		else
		{
			ft_putstr_fd(NOT_FOUND, 2);
			ft_putendl_fd(arg[0], 2);
		}
		return ;
	}
	return ;
}

void	shebang_number_neg(t_core *core, int num)
{
	char *tmp;

	tmp = NULL;
	while (hist->next)
		hist = hist->next;
	while (hist && hist->index > num)
	{
		if (hist->previous)
			hist = hist->previous;
		else
		{
			ft_putendl_fd("Event not Found", 2);
			return ;
		}
	}
	if (hist && hist->index == num)
	{
		return (hist->line);
	}
	return ;
}

// SHEBANG PAS ENCORE INCLUS A METTRE DANS HISTORY BUILTIN P