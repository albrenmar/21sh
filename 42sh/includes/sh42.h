/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:30:16 by bsiche            #+#    #+#             */
/*   Updated: 2018/11/19 15:59:16 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H
# include "../libft/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>

# define K_LEFT		"\x1b\x5b\x44"	
# define K_RIGHT	"\x1b\x5b\x43"
# define K_DOWN		"\x1b\x5b\x42"
# define K_UP		"\x1b\x5b\x41"
# define K_RTN		10
# define K_RT		13
# define K_SPC		32
# define K_BKSP		127
# define K_DEL		"\x1b\x5b\x33\x7e"

typedef struct	s_cursor
{
	int		prompt;
	int		abs;
	int		x;
	int		y;
}				t_cursor;

typedef struct	s_term_data
{
	int		sizex;
	int		sizey;
}				t_term_data;

typedef struct	s_tracking
{
	t_cursor			*pos;
	struct termios		default_term;
	struct termios		myterm;
	struct s_term_data	*terminfo;
	char				*str;
	t_lstcontainer		*key_list;
}				t_tracking;

t_tracking		g_tracking;

char			*ft_usrmode(mode_t mode);

void			ft_printlist();

char			*ft_true_pwd(void);

int				get_key(void);

int				yan_putchar(int c);

void			get_term(void);

void			ft_siginit(void);

void			set_back_term(void);

void			ft_colorstat(void);

int				clear_screen3(void);

int				clear_screen2(void);

void			update_pos(void);

void			add_to_str(char *str);

void			rem_from_str(void);

void			get_size(void);

int				utf_byte(char c);

int				utf_strlen(char *str);

int				get_nb_char(unsigned char c);

int				utf_goto(char *str, int j);
#endif
