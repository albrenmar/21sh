/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:26:51 by hdufer            #+#    #+#             */
/*   Updated: 2019/01/14 15:04:30 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_core *core)
{
	ft_free_tab(core->path);
	ft_free_tab(core->arg);
	free(core->line);
	ft_free_list(core->env);
	// history save in file ./shell_history
	hist_save_file(core->hist);
	exit(1);
}
