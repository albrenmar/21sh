/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 21:55:19 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 22:06:14 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		setfd(int fd, int mode)
{
	static int	fdp = 1;

	if (mode)
		fdp = fd;
	else
		return (fdp);
	return (0);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list		test;
	char		*tmpformat;
	int			i;
	int			temp;
	t_save		save;

	setfd(fd, 1);
	i = 0;
	save.retour = 0;
	tmpformat = ft_strdup(format);
	ft_removestruct(&save, 1);
	va_start(test, format);
	temp = 1;
	while (save.retour != -1 && temp == 1)
	{
		ft_removestruct(&save, 0);
		temp = ft_printstart(&save, tmpformat, &i);
		i = i + (ft_nextarg(test, &save, &tmpformat[i], 0));
	}
	if (save.start != NULL && save.retour != -1)
		ft_putstr_return(save.start, &save);
	va_end(test);
	ft_memdel((void **)&save.start);
	ft_memdel((void **)&tmpformat);
	return (save.retour);
}
