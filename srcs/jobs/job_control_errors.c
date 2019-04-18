/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/03/29 08:07:32 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			job_control_errors(pid_t pid, int mode, int returnvalue)
{
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME": No child process with id ", 2);
		ft_putnbr_fd(pid, 2);
	}
	return (returnvalue);
}
