/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:16:19 by hdufer            #+#    #+#             */
/*   Updated: 2018/03/13 09:16:21 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 1000000
# define CAST(x) ((t_gnl*)x->content)

int					get_next_line(const int fd, char **line);
typedef struct		s_gnl
{
	char			*str;
	int				index;
	int				len;
	int				size;
}					t_gnl;
#endif
