/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:06:23 by mjose             #+#    #+#             */
/*   Updated: 2019/03/03 11:44:12 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "sh42.h"

void			add_to_env_set(char *varname, char *varvalue);
t_env_set		*new_envset(char *varname, char *varvalue);
int				show_setenv(void);
void			replace_env_set_str(char *varname, char *varvalue);
int				cd_builtin(void);
int				check_and_exec_echo(void);
int				is_builtin_alone(void);
int				ft_builtin_search(char *builtin);
int				is_builtin(void);
int				ft_exit(void);
int				builtin_exec(t_last *arglist);
int				jobs_builtin(void);
int				errors_fg(int nb, int error);
int				bg_builtin(void);
int				fg_builtin(void);
int				errors_bg(int nb, int error);

#endif
