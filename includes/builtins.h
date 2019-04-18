/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:06:23 by mjose             #+#    #+#             */
/*   Updated: 2019/04/14 23:47:17 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "sh21.h"

void			free_and_null(void *ptr);
int				ft_exit3(int exitcode, int mode);
int				exit_errors(int error);
int				show_setenv(void);
void			replace_env_set_str(char *varname, char *varvalue);
int				check_and_exec_echo(void);
int				is_builtin_alone(void);
int				ft_builtin_search(char *builtin);
int				is_builtin(void);
int				ft_exit2(int exitcode);
int				unsetenv_errors(int mode);
int				builtin_exec();
int				setenv_errors(int mode);
int				ft_unsetenv(void);
int				ft_setenv(void);
int				jobs_builtin(void);
int				errors_fg(int nb, int error, char *hold);
int				errors_bg(int nb, int error, char *hold);
int				ft_cd(void);
int				getright(char *str, char *err);
int				bg_builtin(void);
int				fg_builtin(void);
int				ft_unset(void);
int				ft_export(void);
int				export_error(char *error);
void			assign_to_env_save_value(char *varname, char *varvalue,
					char *arg);
void			assign_to_env_replace_value(char *varname, char *varvalue,
					char *arg);
void			assign_to_env_if_not_exist(char *varname, char *varvalue,
					char *arg);
int				ft_env(int i, int count);
char			*clean_env_i(char *str, int jsave);
int				builtin_exec_cont_2(void);
int				test_exist_dir(char *path);
char			*add_pwd(char *path);
char			*add_slash(char *pathname);
char			*sanitize_path_cd(char *path);
char			*cd_path(char *path);
void			ft_changedir(char *path, char option, char *err);
#endif
