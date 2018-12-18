/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 02:15:42 by mjose             #+#    #+#             */
/*   Updated: 2018/12/17 04:12:48 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PO line[*i] && line[*i] == '('
# define PF line[*i] && line[*i] == ')'
# define GO line[*i] == '"'

typedef struct		s_tab
{
	char			**tab_word;
	char			**tab_path;
}					t_tab;

typedef struct		s_env2
{
	char			**env;
}					t_env2;

typedef struct		s_tree
{
	char			*str1;
	char			*str_command1;
	char			**cmd1;
	int				com_arg1;
	char			*str2;
	char			*str_command2;
	char			**cmd2;
	int				com_arg2;
	char			*symbol;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_list2
{
	char			*name;
	struct s_list2	*next;
}					t_list2;

typedef struct		s_cmd
{
	struct s_list	*beginlist;
}					t_cmd;

t_tree				*ft_create_tree(char *cmd, t_tree *tree);
void				apply_cmd(/*t_tab *st_tab, t_env2 *st_env,*/
						t_list2 *list_cmd/*, char **env*/);
int					search_symbol(char *cmd);
void				apply_builtin(t_tab *st_tab, t_env2 *st_env,
						char *cmd, char **env);
t_list2				*ft_analize(char *line);
void				free_tree(t_tree *tree);

#endif
