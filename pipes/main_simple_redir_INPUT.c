/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_simple_redir_INPUT.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 02:08:38 by mjose             #+#    #+#             */
/*   Updated: 2018/12/04 05:59:54 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/includes/minishell.h"

#define SIZE 512

#define LEER		0
#define ESCRIBIR	1

int		main(int ac, char **av)
{
//	pid_t	pid;
	int		descrf;
	char	*str;
	char	*tmp;
	char	buf[1024];
	int		bytes;

	str = NULL;
	if (ac < 3)
	{
		printf("Formto: %s fichero comando [opciones].\n", av[0]);
		exit(1);
	}
	printf("Ejemplo de redireccion.\n");
//	if ((pid = fork()) == 0)
//	{
		close(0);
		descrf = open(av[1], O_RDONLY);
		while ((bytes = read(descrf, &buf, sizeof(char))) > 0)
		{
			if (!str)
			{
//				tmp = ft_strdup(str);
//				ft_strdel(&str);
//			}
//			else
				str = ft_strdup("\0");
			}
			tmp = ft_strdup(buf);
			str = ft_strjoin(str, tmp);
		}
		execlp(av[2], str, NULL);
		close(descrf);
		perror(av[0]);
//	}
//	else
//	{
//		waitpid(pid, NULL, 0);
		printf("Hemos creado fichero y escrito en el\n");
		exit(0);
//	}
}