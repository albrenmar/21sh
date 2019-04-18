/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_create_fich.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:42:28 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ctrl_c_heredoc(char *file)
{
	ft_strdel(&file);
	return (1);
}

int		return_success(void)
{
	if (g_tracking.cmd)
		ft_free(g_tracking.cmd);
	ft_free(g_tracking.str);
	return (0);
}

int		proto_heredoc(char *eof, int fd, char *file)
{
	char	*str;

	str = NULL;
	if (g_tracking.interactive == 0)
		return (0);
	while (ft_strcmp(str, eof) != 0 && g_tracking.quotes != 10)
	{
		ft_strdel(&str);
		str = NULL;
		g_tracking.quotes = 3;
		get_key();
		if (g_tracking.quotes == 11)
			return (ctrl_c_heredoc(file));
		str = ft_strdup(g_tracking.cmd);
		ft_strdel(&g_tracking.cmd);
		if (ft_strcmp(str, eof) != 0)
			ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', 2);
	}
	if (str)
		ft_free(str);
	return (return_success());
}

char	*filename(void)
{
	char	*new;
	char	*nbr;

	new = ft_strdup("/tmp/heredoc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		ft_free(new);
		new = ft_strdup("/tmp/heredoc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

char	*exec_create_heredoc(char *eof)
{
	char	*file;
	int		fd;

	file = filename();
	if (!eof)
		return (NULL);
	if ((fd = open(file, O_CREAT | O_RDWR)) == -1)
	{
		ft_putendl_fd("Couldn't create fich in /temp", 2);
		return (NULL);
	}
	if ((proto_heredoc(eof, fd, file)) == 1)
	{
		ft_strdel(&g_tracking.str);
		return (NULL);
	}
	else
		return (file);
}
