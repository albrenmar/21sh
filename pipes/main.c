/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 00:59:52 by mjose             #+#    #+#             */
/*   Updated: 2018/11/28 00:29:21 by mjose            ###   ########.fr       */
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
//	int		b[2];
//	int		readb;
//	int		desc_fitch;
//	char	buf[SIZE];

	if (ac < 3)
	{
		printf("Formto: %s fichero comando [opciones].\n", av[0]);
		exit(1);
	}
//	printf("Ejemplo de redireccion.\n");
//	desc_fitch = open(av[1], O_CREAT|O_TRUNC|O_WRONLY, 0);
//	dup2(desc_fitch, 1);
	pipe(descrf);
//	close(desc_fitch);
//	pipe(a);
//	pipe(b);
	if ((pid = fork()) == 0)
	{
		close(descrf[LEER]);
//		close(b[0]);
		dup2(descrf[ESCRIBIR], 1);
		close(descrf[ESCRIBIR]);
//		execvp(av[2], &av[2]);
		execlp(av[1], av[1], NULL);
		// while ((readb = read(a[0], buf, SIZE)) > 0)
		// 	write(1, buf, readb);
		// ft_strcpy(buf, "Soy tu hijo hablandote por la otra tuberia\n");
		// write(b[1], buf, ft_strlen(buf));
		// close(b[1]);
		perror(av[0]);
	}
	else
	{
		close(descrf[ESCRIBIR]);
		dup2(descrf[LEER], 0);
		close(descrf[LEER]);
		execlp(av[2], av[2], av[3], NULL);
		perror(0);
	// 	close(a[0]);
	// 	close(b[1]);
	// 	ft_strcpy(buf, "Soy tu padre hablandote por una tuberia\n");
	// 	write(a[1], buf, ft_strlen(buf));
	// 	close(a[1]);
	// 	while ((readb = read(b[0], buf, SIZE)) > 0)
	// 		write(1, buf, readb);
	// 	close(b[0]);
	}
	waitpid(pid, NULL, 0);
	exit(0);
}

// int		main(void)
// {
// 	pid_t	pid;
// 	int		p[2];
// 	int		readb;
// 	char	buf[SIZE];

// 	pipe(p);
// 	if ((pid = fork()) == 0)
// 	{
// 		close(p[1]);
// 		while ((readb = read(p[0], buf, SIZE)) > 0)
// 			write(1, buf, readb);
// 		close(p[0]);
// 	}
// 	else
// 	{
// 		close(p[0]);
// 		ft_strcpy(buf, "Esto es lo que hemos leido desde el proceso hijo\n");
// 		write(p[1], buf, ft_strlen(buf));
// 		close(p[1]);
// 	}
// 	waitpid(pid, NULL, 0);
// 	exit(0);
// }
