/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/05 06:33:22 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

void		execute_pipe(void)
{

	printf("j'execute un pipe\n");

}

void		execute_redir(void)
{
	printf("j'execute une redirection\n");
}

void		execute(void)
{
	if (g_tracking.mysh->exec->sym[0][0] == '|')
		execute_pipe();
	if (g_tracking.mysh->exec->sym[0][0] == '>')
		execute_redir();
	printf("commande 1 = %s ------> symbole = %s ------> commande 2 = %s\n", g_tracking.mysh->exec->left[0], g_tracking.mysh->exec->sym[0], g_tracking.mysh->exec->right[0]);
}

void		execute_ast(t_tree *tree)
{
	if (tree->left)
		execute_ast(tree->left);
	if (!g_tracking.mysh->exec->sym)
	{
		if ((tree->name[0] == '|' || tree->name[0] == '&') && ft_strlen(tree->name) == 2)//symbole == || ou &&)
		{
			g_tracking.mysh->exec->left = NULL; //droite est NULL;
			g_tracking.mysh->exec->right = NULL;//gauche est NULL;
		}
		else if (tree->type == OP)
			g_tracking.mysh->exec->sym = tree->cmd;//enregistre symbole;
	}
	if ((!g_tracking.mysh->exec->left || !g_tracking.mysh->exec->right) && !tree->left)//!temp gauche || !temp droite) et pas de branche gauche)
	{
		if (!g_tracking.mysh->exec->left)//!temp gauche)
			g_tracking.mysh->exec->left = tree->cmd;//enregistrer gauche;
		else
			g_tracking.mysh->exec->right = tree->cmd;//enregistrer droite;
	}
	if (g_tracking.mysh->exec->left && g_tracking.mysh->exec->right) //temp gauche et temp droite)
	{
		execute();
		g_tracking.mysh->exec->left = g_tracking.mysh->exec->right;//gauche devient droite;
		g_tracking.mysh->exec->right = NULL;// est NULL;
		g_tracking.mysh->exec->sym = NULL;//symbole est NULL;
		return ;
	}
	if (!g_tracking.mysh->exec->sym && tree->type == OP && (ft_strlen(tree->name) != 2 || (tree->name[0] != '|' && tree->name[0] != '&'))) //pas de symbole et symbole different de || ou &&)
		g_tracking.mysh->exec->sym = tree->cmd;//enregistre symbole;
	if (tree->right)//branche droite)
		execute_ast(tree->right);
	//printf("TEST = %s\n", tree->name);
	//if (!g_tracking.mysh->exec->right)
	//	g_tracking.mysh->exec->right = tree->cmd;
	return ;
}
