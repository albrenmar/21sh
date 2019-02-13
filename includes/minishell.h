/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:22:50 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/13 08:53:17 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PO line[*i] && line[*i] == '('
# define PF line[*i] && line[*i] == ')'
# define GO line[*i] == '"'
#define PA 1
#define OP 2
#define CMD 3
#define ARG 4
#define OPT 5
#define PATH 6

# include "ft_printf.h"
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

typedef struct	s_tab_arg
{
	int		type;
	char	**tab_test;
	struct s_tab_arg	*next;
	struct s_tab_arg	*prev;
}				t_tab_arg;

typedef struct	s_last
{
	int				type;
	char			*name;
	struct s_last	*next;
	struct s_last	*prev;
}				t_last;

typedef struct	s_tree
{
	int			type;
	char		*name;
	char		**cmd;
	struct s_tree	*prev;
	struct s_tree	*right;
	struct s_tree	*left;
}				t_tree;

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
void			insert_node(t_last *ref_node, t_last *insert);
t_last			*create_new_list(void);
void			ft_lexeur(t_last *list_cmd);
int				error_lexer(t_last *list_cmd);
void			tri_lexer(t_last *list_cmd);
t_last			*ft_parseur(char *line);
void			ft_ast(t_tab_arg *tab_arg);
t_tab_arg		*convert_to_list_tab(t_last	*list);
void			execute_ast(t_tree *tree, t_tab_arg *tab_arg);
void			execute_pipe(void);
void			execute_pipe_two(void);
void			test_pipe(void);
void			test_redir(void);
char			**test_exist_fonction(char **tab_cmd);
void			execute_two(void);
void			add_to_exec(int mode);
void			exec_command(void);

#endif
