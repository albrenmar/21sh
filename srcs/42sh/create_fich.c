/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fich.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:24:49 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/25 01:21:25 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		next_set_fd(int fd_in, int fd)
{
	if (fd_in == 0)
		g_tracking.mysh->set_fd->STDIN = fd;
	else if (fd_in == 1)
		g_tracking.mysh->set_fd->STDOUT = fd;
	else if (fd_in == 2)
		g_tracking.mysh->set_fd->STDERR = fd;
	else if (fd_in == 3)
		g_tracking.mysh->set_fd->three = fd;
	else if (fd_in == 4)
		g_tracking.mysh->set_fd->four = fd;
	else if (fd_in == 5)
		g_tracking.mysh->set_fd->five = fd;
	else if (fd_in == 6)
		g_tracking.mysh->set_fd->six = fd;
	else if (fd_in == 7)
		g_tracking.mysh->set_fd->seven = fd;
	else if (fd_in == 8)
		g_tracking.mysh->set_fd->eight = fd;
	else if (fd_in == 9)
		g_tracking.mysh->set_fd->nine = fd;
}

int			len_input_fd(char *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = NULL;
	while (str[i] && str[i] > 47 && str[i] < 58)
		i++;
	if (i > 0)
	{
		str2 = ft_strndup(str, i);
		i = ft_atoi(str2);
		free(str2);
	}
	else
		i = 1;
	return (i);
}

int			set_reddir_to_fd(t_last *list, int i)
{
	FILE	*fd_open;
	int		fd_in;
	int		fd_out;

	fd_open = NULL;
	fd_in = 0;
	fd_out = 0;
	if ((fd_in = len_input_fd(list->name)) > 9 || (list->next && (fd_out = len_input_fd(list->next->name)) > 9))
	{
		ft_putendl_fd("42sh: Bad file descriptor", 2);
		return (-1);
	}
	if (list->next && list->next->name[0] > 47 && list->next->name[0] < 58)
	{
		fd_open = fdopen(list->next->name[0] - '0', "r+");
		if (!fd_open)
		{
			ft_putendl_fd("42sh: Bad file descriptor", 2);
			return (-1);
		}
	}
	else if (list->next && (ft_strlen(list->next->name) == 1) && !ft_strcmp(list->next->name, "-"))
		fd_out = open("/dev/null", O_WRONLY);
	else
	{
		ft_putendl_fd("42sh: Bad file descriptor", 2);
		return (-1);
	}
	next_set_fd(fd_in, fd_out);
	return (0);
}

void		set_reddir_fd(t_last *list)
{
	t_last	*temp;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 0;
	temp = NULL;
	temp = list;
	fd_in = len_input_fd(temp->name);
	while (temp->type != FICH)
		temp = temp->next;
	fd_out = open(temp->name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_in < 10)
		next_set_fd(fd_in, fd_out);
}

int		create_fich(t_last *list)
{
	int		i;
	t_last	*temp;

	i = 0;
	temp = list;
	if (its_reddir_to_fd(list))
	{
		if (set_reddir_to_fd(list, i) == -1)
			return (-1);
	}
	else if (its_reddir(list))
	{
		while (list->type != FICH)
			list = list->next;
		if (g_tracking.mysh->set_fd->STDOUT != 1)
			close(g_tracking.mysh->set_fd->STDOUT);
		if (ft_strlen(temp->name) == 1)
			g_tracking.mysh->set_fd->STDOUT = open(list->name, O_CREAT
				| O_TRUNC | O_RDWR, 0644);
		else
			g_tracking.mysh->set_fd->STDOUT = open(list->name, O_CREAT
				| O_APPEND | O_RDWR, 0644);
	}
	else if (its_fd_reddir(list))
		set_reddir_fd(list);
	return (0);
}
