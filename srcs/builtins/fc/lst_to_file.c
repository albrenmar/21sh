/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:28:02 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/25 23:03:51 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		rev_to_file(t_fcparse *opt, int fd)
{
	t_list		*tmp;

	tmp = ft_lstget(opt->max, g_tracking.mysh->hist->firstelement);
	while (tmp && (int)tmp->index > (opt->low - 1))
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->prev;
	}
	return (0);
}

int		fc_to_file(t_fcparse *opt, int fd)
{
	t_list		*tmp;

	if (!opt || fd == -1)
		return (1);
	if (opt->r == 0)
	{
		tmp = ft_lstget(opt->low - 1, g_tracking.mysh->hist->firstelement);
		while (tmp && (int)tmp->index < (opt->max + 1))
		{
			ft_putendl_fd(tmp->content, fd);
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (rev_to_file(opt, fd));
}

char	*fc_filename(void)
{
	char	*new;
	char	*nbr;

	new = ft_strdup("/tmp/fc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		ft_free(new);
		new = ft_strdup("/tmp/fc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

void	print_filename(char *file)
{
	char	*str;
	int		i;
	int		fd;

	i = 1;
	ft_putendl("DEBUT PRINT FCFILE");
	if ((fd = open(file, O_RDWR)) == -1)
		ft_putendl_fd("Couldn't create file in /tmp", 2);
	while (get_next_line(fd, &str) > 0)
	{
		ft_putnbr(i);
		ft_putstr(" : ");
		ft_putendl(str);
		i++;
	}
	ft_putendl("FIN PRINT FCFILE");
}

int		create_fc_file(t_fcparse *opt)
{
	char	*file;
	int		fd;

	get_neg_offset(opt);
	if (!opt)
		return (-1);
	file = NULL;
	fd = 0;
	file = fc_filename();
	if (!file)
		return (-1);
	if ((fd = open(file, O_CREAT | O_RDWR)) == -1)
		ft_putendl_fd("Couldn't create file in /tmp", 2);
	if ((fc_to_file(opt, fd)) == 1)
		return (-1);
	close(fd);
	print_filename(file);
	close(fd);
	fc_loop(file);
	ft_free(file);
	return (0);
}
