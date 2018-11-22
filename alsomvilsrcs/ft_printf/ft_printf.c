/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 03:18:32 by alsomvil          #+#    #+#             */
/*   Updated: 2018/08/25 22:05:15 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <locale.h>

char	*ft_checkarg(t_save *save, char *str, int *temp, int i)
{
	char	*stockarg;

	while (str[i] && str[i] != 's' && str[i] != 'S' && str[i] != 'p'
			&& str[i] != 'd' && str[i] != 'D' && str[i] != 'i'
			&& str[i] != 'o' && str[i] != 'O' && str[i] != 'u'
			&& str[i] != 'U' && str[i] != 'x' && str[i] != 'X'
			&& str[i] != 'c' && str[i] != 'C' && str[i] != '%')
	{
		i++;
		(*temp)++;
	}
	stockarg = ft_strndup(str, i);
	save->conversion = str[i];
	return (stockarg);
}

int		ft_nextarg(va_list test, t_save *save, char *tmpformat, int i)
{
	int		temp;
	int		j;
	char	*nextarg;

	temp = 0;
	j = 0;
	nextarg = NULL;
	while (tmpformat[i] && tmpformat[i] != '%')
		i++;
	if (tmpformat[i] == '%')
	{
		nextarg = ft_checkarg(save, &tmpformat[i + 1], &temp, 0);
		if (nextarg != NULL)
			ft_stockmodif(save, nextarg, 0, temp);
		ft_apply(test, save);
		ft_memdel((void **)&nextarg);
	}
	return (temp + 2);
}

int		ft_printstart(t_save *save, char *tmpformat, int *i)
{
	int		length;
	int		start;

	length = 0;
	start = *i;
	while (tmpformat[*i] && tmpformat[*i] != '%')
	{
		length++;
		(*i)++;
	}
	save->start = ft_strndup(&tmpformat[start], length);
	if (tmpformat[*i] == '%')
		return (1);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		test;
	char		*tmpformat;
	int			i;
	int			temp;
	t_save		save;

	i = 0;
	setfd(1, 1);
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
