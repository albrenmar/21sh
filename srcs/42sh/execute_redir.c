/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:09:42 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/11 20:20:00 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

void		execute_redir_two(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		dprintf(2, "LE FICHIER A CREER EST = %s\n", g_tracking.mysh->exec->right[0]);
		open(g_tracking.mysh->exec->right[0], O_CREAT ,0644);
		exit(0);
		//execute_two();
	}
	else
	{
		//wait(&g_tracking.mysh->exec->pid_exec);
		wait(NULL);
	}
}

void		execute_redir(void)
{
	pid_t	pid0;

	g_tracking.mysh->exec->pid_exec = (pid0 = fork());
	if (pid0 == 0)
	{
		dprintf(2, "LE FICHIER A CREER EST = %s\n", g_tracking.mysh->exec->right[0]);
		open(g_tracking.mysh->exec->right[0], O_CREAT, 0644);
		exit(0);
		//execute_two();
	}
	else
	{
		wait(NULL);
		//wait(&pid0);
	}
}

void	test_redir(void)
{
	/*dprintf(2, "LEFT = %s\n", g_tracking.mysh->exec->left[0]);
	  dprintf(2, "RIGHT = %s\n", g_tracking.mysh->exec->right[0]);
	  dprintf(2, "SYM = %s\n", g_tracking.mysh->exec->sym[0]);
	printf("C'est une redirection\n");*/
	//execute_pipe_two();
//	exit (0);
}

/*void	execute_first_redir(t_ast *ast_cmd, char **tablist)
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
*/
