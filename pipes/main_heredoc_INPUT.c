/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc_INPUT.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 01:15:58 by mjose             #+#    #+#             */
/*   Updated: 2018/12/19 04:58:59 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/includes/minishell.h"

#define SIZE 512

#define LEER		0
#define ESCRIBIR	1

int		main(int ac, char **av)
{
	pid_t	pid;
	int		descrf[2];
	char		*line;

	if (ac < 3)
	{
		printf("Formto: %s fichero comando [opciones].\n", av[0]);
		exit(1);
	}
	pipe(descrf);
	if ((pid = fork()) == 0)
	{
		close(descrf[LEER]);
		dup2(descrf[ESCRIBIR], 1);
		close(descrf[ESCRIBIR]);
		while (get_next_line(0, &line))
		{
			if (!ft_strequ(line, av[2]))
				ft_putendl_fd(line, 1);
			else
				exit(0) ;
		}
	//	execlp(av[1], av[1], NULL);
	//	perror(av[0]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(descrf[ESCRIBIR]);
		dup2(descrf[LEER], 0);
		close(descrf[LEER]);
		execlp(av[1], av[1], NULL);
		perror(0);
	}
	waitpid(pid, NULL, 0);
	exit(0);
}
