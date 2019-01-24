/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:22:50 by alsomvil          #+#    #+#             */
/*   Updated: 2019/01/24 00:38:50 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PO line[*i] && line[*i] == '('
# define PF line[*i] && line[*i] == ')'
# define GO line[*i] == '"'

# include "ft_printf.h"
//# include "job_control.h"
# include <termios.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>

typedef struct	s_tab
{
	char	**tab_word;
	char	**tab_path;
}				t_tab;

typedef struct	s_env
{
	char	**env;
}				t_env;

typedef struct	s_ast
{
	char			*cmd;
	int				next_token;
	struct s_ast	*next;
	struct s_ast	*prev;
}				t_ast;

typedef struct	s_last
{
	char			*name;
	struct s_last	*next;
}				t_last;

typedef struct	s_cmd
{
	struct s_list	*beginlist;
}				t_cmd;

int				ft_strcmp(const char *s1, const char *s2);
int				nb_env(char **env);
int				check_is_env(char *str);
void			forfree(char **tab);
int				verif_char(char *line);
void			search_and_affich_env(char *tab, char **env);
char			*recup_path(char **env, char *str);
void			modif_pwd(char **env, char *str);
int				get_next_line(const int fd, char **line);
char			**ft_split_whitespaces(char *str);
char			**ft_strsplit(char const *s, char c);
void			set_env(t_env *st_env, char **env);
void			ft_unsetenv(t_env *st_env, t_tab *st_tab);
void			affich_env(t_env *st_env, t_tab *st_tab);
char			*get_pwd(char **env);
void			change_pwd(char ***env, char *pwd);
void			change_last_pwd(char **env, char *pwd);
char			*get_last_pwd(char **env);
void			ft_echo(t_tab *st_tab, t_env *st_env);
void			ft_cd(t_env *st_env, t_tab *st_tab);
void			ft_setenv(t_env *st_env, t_tab *st_tab);
void			realize_built(t_tab *st_tab, t_env *st_env,
		char **line, char **env);
int				check_is_builtins(t_tab *st_tab);
int				existe_env(char **env, char *str);
void			modif_env(char **env, char *str);
char			**duplicate_tab(char ***tab);
char			**duplicate_tab_two(char ***tab, int j);
char			**duplicate_env(char **tab);
void			create_env(char ***env, char *str);
void			delete_env(char ***env, char *str);
void			freetab(char **tab);
void			apply_cmd(t_tab *st_tab, t_env *st_env,
		t_last *list_cmd);
int				search_symbol(char *cmd);
void			apply_builtin(t_tab *st_tab, t_env *st_env,
		char *cmd);
t_last			*ft_analize(char *line);
int				add_alias(char *alias);
void			print_alias_lst(void);
int				unalias(char *alias);

/*
t_last				*find_job (pid_t pgid);
int					job_is_stopped(t_last *job_list);
int					job_is_completed(t_last *job_list);
void				init_shell_for_job(void);
void				launch_process(t_ast *process_list, pid_t pgid, int infile, int outfile, int errfile, int foreground);
void				launch_job(t_last *job_list, int foreground);
void				put_job_in_foreground(t_last *job_list, int cont);
void				put_job_in_background(t_last *job_list, int cont);
int					mark_process_status(pid_t pid, int status);
void				update_status(void);
void				wait_for_job(t_last *job_list);
void				format_job_info(t_last *job_list, const char *status);
void				do_job_notification(void);
void				mark_job_as_running(t_last *job_list);
void				continue_job(t_last *job_list, int foreground);
*/
t_ast	*new_first_list(t_ast *ast_cmd, int mode);
void	create_ast(char *cmd_full, t_ast *ast_cmd);

#endif
