/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_simple_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 02:08:38 by mjose             #+#    #+#             */
/*   Updated: 2018/12/04 05:06:23 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/includes/minishell.h"

#define SIZE 512

#define LEER		0
#define ESCRIBIR	1

int		main(int ac, char **av)
{
	pid_t	pid;
	int		descrf;

	if (ac < 3)
	{
		printf("Formto: %s fichero comando [opciones].\n", av[0]);
		exit(1);
	}
	printf("Ejemplo de redireccion.\n");
	if ((pid = fork()) == 0)
	{
		close(1);
		descrf = open(av[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		execlp(av[2], av[2], NULL);
		close(descrf);
		perror(av[0]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("Hemos creado fichero y escrito en el\n");
		exit(0);
	}
}