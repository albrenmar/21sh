/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:47:54 by mjose             #+#    #+#             */
/*   Updated: 2019/02/24 05:08:22 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

void			add_to_env_set(char *varname, char *varvalue);
t_env_set		*new_envset(char *varname, char *varvalue);
int				show_setenv(void);
void			replace_env_set_str(char *varname, char *varvalue);

#endif
