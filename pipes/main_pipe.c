/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 01:53:00 by mjose             #+#    #+#             */
/*   Updated: 2018/12/04 01:54:22 by mjose            ###   ########.fr       */
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
		execlp(av[1], av[1], NULL);
		perror(av[0]);
	}
	else
	{
		close(descrf[ESCRIBIR]);
		dup2(descrf[LEER], 0);
		close(descrf[LEER]);
		execlp(av[2], av[2], av[3], NULL);
		perror(0);
	}
	waitpid(pid, NULL, 0);
	exit(0);
}
