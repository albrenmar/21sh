/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:20:04 by mjose             #+#    #+#             */
/*   Updated: 2018/12/17 07:28:24 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_existence_and_clean(t_proc *proc, char *tmp_path, char *tmp_com)
{
	if (!access(tmp_path, F_OK))
	{
		put_err_comnp(tmp_path, proc);
		ft_strdel(&tmp_path);
		ft_strdel(&tmp_com);
		return (1);
	}
	ft_strdel(&tmp_path);
	return (0);
}

void	stop_child(int father)
{
	kill(father, SIGTSTP);
}

void	exec_child_command_path(t_com *com, t_env *env, t_proc *proc)
{
	int		i;
	char	*tmp_com;
	char	*tmp_path;
	pid_t	father;

	i = 0;
	tmp_com = ft_strjoin("/", com->tab_command[0]);
	if (env->tab_exec && !ft_strequ(com->tab_command[0], ".") &&
			!ft_strequ(com->tab_command[0], ".."))
		while (env->tab_exec[i])
		{
			tmp_path = ft_strjoin(env->tab_exec[i++], tmp_com);
			if (!access(tmp_path, X_OK))
			{
				if ((father = fork()) == 0)
					execve(tmp_path, com->tab_command, env->tab_env);
				signal(SIGINT, SIG_IGN);
				signal(SIGTSTP, &stop_child);
				wait(&proc->stat_process);
//				if (WIFSIGNALED(proc->stat_process))
//					ft_putchar_fd('\n', STDIN_FILENO);
				ft_strdel(&tmp_path);
				free(tmp_com);
				return ;
			}
			else if (test_existence_and_clean(proc, tmp_path, tmp_com))
				return ;
		}
	put_err_comnf(com, proc, tmp_com);
}

void	exec_child_command_path_piped(t_com *com, t_env *env, t_proc *proc)
{
	int		i;
//	char	*tmp_com;
	char	*tmp_com1;
	char	*tmp_com2;
	char	*tmp_path;
	pid_t	father;
	int		fd[2];

	i = 0;
//	tmp_com = ft_strjoin("/", com->tab_command[0]);
	tmp_com1 = ft_strjoin("/", com->tree->cmd1[0]);
	tmp_com2 = ft_strjoin("/", com->tree->cmd2[0]);
/*	if (env->tab_exec && !ft_strequ(com->tab_command[0], ".") &&
			!ft_strequ(com->tab_command[0], ".."))
*/	if (env->tab_exec && !ft_strequ(com->tree->cmd1[0], ".") &&
			!ft_strequ(com->tree->cmd1[0], "..") &&
			!ft_strequ(com->tree->cmd2[0], ".") &&
			!ft_strequ(com->tree->cmd2[0], ".."))
		while (env->tab_exec[i])
		{
			tmp_path = ft_strjoin(env->tab_exec[i++], tmp_com1);
			if (!access(tmp_path, X_OK))
			{
				pipe(fd);
				if ((father = fork()) == 0)
				{
					close(fd[READ]);		
					dup2(fd[WRITE],1 );
					close(fd[WRITE]);
//					execve(tmp_path, com->tab_command, env->tab_env);
					execve(tmp_path, com->tree->cmd1, env->tab_env);
				}
				else
				{
					i = 0;
					ft_strdel(&tmp_path);
					while (env->tab_exec[i])
					{
						tmp_path = ft_strjoin(env->tab_exec[i++], tmp_com2);
						if (!access(tmp_path, X_OK))
						{
//							wait(&proc->stat_process);
							if ((father = fork()) == 0)
							{
								close(fd[WRITE]);
								dup2(fd[READ], 0);
								close(fd[READ]);
								execve(tmp_path, com->tree->cmd2, env->tab_env);
							}
						}
					}
				}
				signal(SIGINT, SIG_IGN);
				signal(SIGTSTP, &stop_child);
				wait(&proc->stat_process);
//				if (WIFSIGNALED(proc->stat_process))
//					ft_putchar_fd('\n', STDIN_FILENO);
				ft_strdel(&tmp_path);
//				free(tmp_com);
				free(tmp_com1);
				free(tmp_com2);
				return ;
			}
//			else if (test_existence_and_clean(proc, tmp_path, tmp_com))
//				return ;
		}
	put_err_comnf(com, proc, tmp_com1);
	put_err_comnf(com, proc, tmp_com2);
}

void	exec_child_other(t_com *com, t_env *env, t_proc *proc)
{
	char	*error;
	pid_t	father;

	if (!access(com->tab_command[0], X_OK))
	{
		if ((father = fork()) == 0)
			execve(com->tab_command[0], com->tab_command, env->tab_env);
		wait(&proc->stat_process);
		return ;
	}
	error = ft_strjoin("minishell: command not found: ", com->tab_command[0]);
	ft_putendl_fd(error, 2);
	free(error);
}

void	exec_child(t_com *com, t_env *env, t_proc *proc)
{
	check_arg_for_child(com, env);
	if ((com->tab_command[0][0] == '.' && com->tab_command[0][1] == '/') ||
			com->tab_command[0][0] == '/' || com->tab_command[0][0] == '~')
		exec_child_other(com, env, proc);
	else
		exec_child_command_path(com, env, proc);
}

void	exec_child_piped(t_com *com, t_env *env, t_proc *proc)
{
/*	check_arg_for_child(com, env);
	if ((com->tab_command[0][0] == '.' && com->tab_command[0][1] == '/') ||
			com->tab_command[0][0] == '/' || com->tab_command[0][0] == '~')
		exec_child_other(com, env, proc);
	else*/
		exec_child_command_path_piped(com, env, proc);
}

void	exec_adv_command(t_env *env, t_prompt *prompt, t_com *com, t_proc *proc)
{
/*	if (check_type_cmd(com->tab_command[0]) > 0)
	{
		exec_builtin(com, env);
		prompt->have_line = 0;
		ft_strdel(&prompt->line);
		put_prompt(env, prompt);
	}
	else if (check_type_cmd(com->tree->tab_command[0]) == 0)
	{
		exec_child(com, env, proc);
		prompt->have_line = 0;
		ft_strdel(&prompt->line);
		if (WIFSIGNALED(proc->stat_process) || WIFSTOPPED(proc->stat_process))
		{
			ft_putchar('\n');
			put_prompt(env, prompt);
			signal(SIGINT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			if (WIFSTOPPED(proc->stat_process))
				ft_putendl("Hemos presionado CTRL+Z");
		}
		else if (WIFEXITED(proc->stat_process))
			put_prompt(env, prompt);
	}
	rmv_comtab(com);
*/	if (ft_strequ(com->tree->symbol, "|"))
	{
		exec_child_piped(com, env, proc);
		if (!WIFEXITED(proc->stat_process))
			put_prompt(env, prompt);
	}
}

void	exec_command(t_env *env, t_prompt *prompt, t_com *com, t_proc *proc)
{
	if (check_type_cmd(com->tab_command[0]) > 0)
	{
		exec_builtin(com, env);
		prompt->have_line = 0;
		ft_strdel(&prompt->line);
		put_prompt(env, prompt);
	}
	else if (check_type_cmd(com->tab_command[0]) == 0)
	{
		exec_child(com, env, proc);
		prompt->have_line = 0;
		ft_strdel(&prompt->line);
		if (WIFSIGNALED(proc->stat_process) || WIFSTOPPED(proc->stat_process))
		{
			ft_putchar('\n');
			put_prompt(env, prompt);
			signal(SIGINT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);
			if (WIFSTOPPED(proc->stat_process))
				ft_putendl("Hemos presionado CTRL+Z");
		}
		else if (WIFEXITED(proc->stat_process))
			put_prompt(env, prompt);
	}
	rmv_comtab(com);
}
