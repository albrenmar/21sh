/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 01:05:10 by mjose             #+#    #+#             */
/*   Updated: 2019/01/30 03:58:28 by mjose            ###   ########.fr       */
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
	struct s_expand	*next;
}				t_expand;

typedef struct	s_args
{
	struct s_keyval	*param;
	struct s_args	*next;
}				t_args;

void			expand_transformer(char *line);
int				need_expand(char *to_transf);
t_expand		*new_expand(void);
void			create_list_expand(t_expand *new_letter, char *line);
int				have_homedir(char *to_transf);
int				check_have_homedir(struct passwd *user_inf, char *tmp_usr);
int				have_parm(char *to_transf);
int				is_to_add_or_mod_parm(char *to_transf);
void			transform(t_expand *expand, char **str);
void			expand_tilde_only(char **str);

#endif
