/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:11:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/11 15:51:49 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../Libft/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup((char*)s2));
	else if (s2 == NULL)
		return (ft_strdup((char*)s1));
	sjoin = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (sjoin == NULL)
		return (NULL);
	ft_strcpy(sjoin, s1);
	ft_strcat(sjoin, s2);
	return (sjoin);
}

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

/*int		main(int ac, char **av)
{
	pid_t		pid;
	int			descrf;
	char		*str;
	char		*tmp;
	char		buf[1024];
	int			bytes;

	str = NULL;
	if (ac < 3)
	{
		printf("Formto: %s fichero comando [opciones].\n", av[0]);
		exit(1);
	}
	printf("Ejemplo de redireccion.\n");
	if ((pid = fork()) == 0)
	{
		close(0);
		descrf = open(av[1], O_WRONLY);
		while ((bytes = read(descrf, &buf, sizeof(char))) > 0)
		{
			if (!str)
			{
				tmp = ft_strdup(str);
				ft_strdel(&str);
			}
			else
				str = ft_strdup("\0");
		}
		tmp = ft_strdup(buf);
		str = ft_strjoin(str, tmp);
		execlp(av[2], str, NULL);
		perror(av[0]);
	}
	close(descrf);
	//else
	//{
	waitpid(pid, NULL, 0);
	printf("Hemos creado fichero y escrito en el\n");
	exit(0);
	//}
}*/
