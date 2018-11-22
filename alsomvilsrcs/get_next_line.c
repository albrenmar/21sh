/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:42:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/09/13 15:07:07 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_nextline(char *str, char **line, int mode)
{
	int		i;
	char	*save;

	i = 0;
	if (mode)
	{
		while (str[i])
		{
			if (str[i] == '\n')
			{
				*line = ft_strndup(str, i);
				if (str[i + 1])
					save = ft_strdup(&str[i + 1]);
				else
					save = NULL;
				return (save);
			}
			i++;
		}
	}
	else
		while (str[i])
			if (str[i++] == '\n')
				return (str);
	return (NULL);
}

t_fd	*checkfd(t_fd **begin_list, int fd)
{
	t_fd *tmp;

	tmp = *begin_list;
	if (tmp == NULL)
	{
		if (!(tmp = ft_memalloc(sizeof(t_fd))))
			return (NULL);
		tmp->fd = fd;
		*begin_list = tmp;
		return (tmp);
	}
	while (tmp && tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			if (!(tmp->next = ft_memalloc(sizeof(t_fd))))
				return (NULL);
			tmp->next->fd = fd;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int		gnlparttwo(int ret, t_fd *tmp, char **line, char *buf)
{
	char	*str;

	str = ft_memalloc(1);
	while ((ret = read(tmp->fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(tmp->free = ft_strjoin(str, buf)))
			return (-1);
		free(str);
		str = tmp->free;
		if (ft_nextline(str, NULL, 0))
		{
			tmp->save = ft_nextline(str, line, 1);
			free(str);
			ft_bzero(buf, BUFF_SIZE + 1);
			return (1);
		}
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (ret >= 0 && str[0] != '\0')
	{
		*line = str;
		return (1);
	}
	free(str);
	return (ret < 0 ? -1 : 0);
}

int		gnlparthree(char **line, t_fd *tmp, char *buf, char *str)
{
	int	ret;

	ret = 0;
	while (!(ft_nextline(tmp->save, NULL, 0)))
	{
		if ((ret = read(tmp->fd, buf, BUFF_SIZE)) > 0)
		{
			if (ret < 0 || !(str = ft_strjoin(tmp->save, buf)))
				return (-1);
			ft_memdel((void**)&tmp->save);
			tmp->save = str;
			ft_bzero(buf, BUFF_SIZE + 1);
		}
		else if (tmp->save != NULL)
		{
			if (!(*line = ft_strdup(tmp->save)))
				return (-1);
			tmp->save = NULL;
			return (1);
		}
		else
			return (0);
	}
	tmp->save = ft_nextline(tmp->save, line, 1);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			*str;
	char			buf[BUFF_SIZE + 1];
	static t_fd		*begin_list = NULL;
	t_fd			*tmp;

	str = NULL;
	if (fd < 0 || line == NULL || !(tmp = checkfd(&begin_list, fd)))
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	if (tmp->save != NULL)
	{
		return (gnlparthree(line, tmp, buf, str));
	}
	return (gnlparttwo(0, tmp, line, buf));
}
