/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:05:10 by mjose             #+#    #+#             */
/*   Updated: 2019/02/04 04:35:23 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"
# include "minishell.h"
# include <pwd.h>
# include <uuid/uuid.h>

typedef struct	s_expand
{
	char			ltr;
	int				len;
	int				idx;
	struct s_expand	*next;
	struct s_expand	*prev;
}				t_expand;

typedef struct	s_args
{
	struct s_keyval	*param;
	struct s_args	*next;
}				t_args;

void			expand_transformer(t_last *cmd);
int				need_expand(char *to_transf);
t_expand		*new_expand(int len);
void			create_list_expand(t_expand *new_letter, char *line);
int				have_homedir(char *to_transf);
int				check_have_homedir(struct passwd *user_inf, char *tmp_usr);
int				have_parm(char *to_transf);
int				is_to_add_or_mod_parm(char *to_transf);
void			transform(t_expand *expand, char **str);
void			expand_tilde_only(char **str);
char			*get_user_home(char *user);
void			expand_tilde_path(char **str, t_expand **expand);
int				is_path_tilde(char *to_transf);
void			delete_list_expand(t_expand **letter);
void			delete_letter_expand(t_expand **letter);
void			update_list_expand(t_expand **letter, char **str);
char			*get_home_value(void);
char			*get_parm_string(char *str);
void			expand_tilde_user(char **str, t_expand **expand);
void			expand_tilde_pwd(char **str, t_expand **expand);
void			expand_keys(t_expand *expand, char **str);
char			check_sign(t_expand *expand);
void			exp_key_less(char **str, t_expand *expand);
char			*get_varname(t_expand *expand);
char			*get_value(t_expand *expand);
void			exp_key_equal(char **str, t_expand *expand);
void			exp_key_inter(char **str, t_expand *expand);

#endif
