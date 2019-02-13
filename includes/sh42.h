/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:30:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/13 08:12:20 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H
# include "libft.h"
# include "ft_ls.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <fcntl.h>

# define USER		"alsomvil"
# define K_FN1		"\x1b\x4f\x50"
# define K_FN2		"\x1b\x4f\x51"
# define K_FN3		"\x1b\x4f\x52"
# define K_LEFT		"\x1b\x5b\x44"
# define K_RIGHT	"\x1b\x5b\x43"
# define K_DOWN		"\x1b\x5b\x42"
# define K_UP		"\x1b\x5b\x41"
# define K_LUP		"\x1b\x5b\x31\x3b\x32\x41"
# define K_LDOWN	"\x1b\x5b\x31\x3b\x32\x42"
# define K_WLEFT	"\x1b\x5b\x31\x3b\x32\x44"
# define K_WRIGHT	"\x1b\x5b\x31\x3b\x32\x43"
# define K_RTN		10
# define K_RT		13
# define K_SPC		32
# define K_BKSP		127
# define K_TAB		9
# define K_DEL		"\x1b\x5b\x33\x7e"

int		descrf[2];
int		descrf_two[2];

typedef struct	s_cursor
{
	int		prompt;
	int		abs;
	int		x;
	int		y;
	int		relabs;
	int		relx;
	int		rely;
	int		legacy;
}				t_cursor;

typedef struct	s_term_data
{
	int		sizex;
	int		sizey;
}				t_term_data;

typedef struct	s_auto
{
	char			*word;
	char			*path;
	char			*menuline;
	t_lstcontainer	*bin_lst;
	t_lstcontainer	*var_lst;
	t_lstcontainer	*comp_list;
	t_lstcontainer	*to_free;
	t_lstcontainer	*page_lst;
	int				active_page;
	int				per_page;
	int				page_nbr;
	int				type;
	char			*to_add;
	int				col_nbr;
	int				lin_nbr;
	int				size;
	int				line_up;
	int				last_page;
	int				pad_lpage;
}				t_auto;

typedef struct	s_cpaste
{
	int		b1;
	int		b2;
	char	*line;
}				t_cpaste;

typedef struct	s_keyval
{
	char	*key;
	char	*value;
}				t_keyval;

typedef struct			s_hist
{
	struct s_hist	*next;
	struct s_hist	*previous;
	int				index;
	char			*line;
}						t_hist;

typedef struct			s_order
{
	int		type;
	char	**command;
	char	*sym;
	struct	s_order	*next;
	struct	s_order	*prev;
	struct	s_order	*temp_command;
	struct	s_order	*temp_command_next;
}						t_order;

typedef struct			s_exec
{
	pid_t	gpid;
	pid_t	pid_exec;
	int		ret;
	int		i;
	char	*fich;
	char	**left;
	char	**right;
	char	**sym;
}						t_exec;

typedef struct	s_shell
{
	t_lstcontainer	*alias_lst;
	t_lstcontainer	*env;
	t_hist			*hist;
	t_exec			*exec;
	t_order			*order;
}				t_shell;

typedef struct	s_tracking
{
	t_cursor			*pos;
	struct termios		default_term;
	struct termios		myterm;
	struct s_term_data	*terminfo;
	struct s_cpaste		*cpaste;
	struct s_auto		*aut;
	struct s_shell		*mysh;
	char				*str;
	char				*cmd;
	char				*comp;
	char				*prompt;
	t_lstcontainer		*key_list;
	int					swi;
	int					buffsize;
	int					histindex;
	int					histmax;
}				t_tracking;

t_tracking		g_tracking;

void			init_shell(char **environ);

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

void			rem_from_str_del(void);

void			get_size(void);

int				utf_byte(char c);

int				utf_strlen(char *str);

int				get_nb_char(unsigned char c);

int				utf_goto(char *str, int j);

void		    print_line(void);

void			correct_pos(void);

void			back_to_pos(void);

void			move_to_end();

void			move_left(void);

void			move_right(void);

void			back_home(void);

void			go_to_pos(void);

void			cursorinit(void);

void			cursor_reset(void);

void			move_up(void);

int				check_up(void);

void			move_down(void);

int				check_down(void);

void			next_word(void);

void			prev_word();

int				rev_utf_goto(char *str, int j);

void			begin_cpy(void);

void			begin_paste(void);

void			print_line_cpy(int start, int end);

t_lstcontainer	*modified_ls(int argc, char **argv);

int				auto_complete(void);

void			get_line_col(void);

void			get_max_size(void);

void			ft_strpadding(void);

t_lstcontainer	*build_ls(void);

int				ft_easyprint(t_list *liste);

void			print_list(void);

void			build_comp(t_lstcontainer *list);

void			completion_loop(t_lstcontainer *list);

void			complete_usr_word(void);

void			complete_usr_var(void);

void			rem_str(char *str);

void			assign_type(void);

void			clean_up_autoc(void);

int				ft_menuline(void);

char			*send_color(int i);

void			color(t_list *liste);

int				print_menu(void);

void			end_autocomplete(int i);

void			build_bin_lst(void);

t_list			*move_arround(t_list *buf, int i);

void			set_up_page(void);

t_lstcontainer *build_page_lst(t_lstcontainer *list);

void			build_var_lst();

void			print_list2(t_lstcontainer *list);

void			change_page(int i, t_lstcontainer *list);

void			join_page_nbr(void);

void			line_per_page(void);

void			escape_path(void);

t_lstcontainer	*change_dir(void);

int				init_alias(void);

int				add_alias(char *alias);

t_keyval		*parse_alias(char *alias);

int				ft_build_test(char *string);

int				two_arg(char **argv);

int				three_arg(char **argv);

t_lstcontainer	*type_ls(int argc, char **argv);

char			*get_env_string(char *str);

t_lstcontainer	*ft_env_to_lst(char **environ);

int				replace_env_str(char *s1, char *s2);

void			ft_add_env_string(char *s1, char *s2);

char			*remove_env_string(char *str);

char			*ft_true_pwd(void);

void			add_missing_string();


void							hist_file_to_lst(void);
int								print_hist();
int								get_last();
int								go_to(int i);
int								history_up(void);
int								history_down(void);
t_hist                         	*hist_lst_create(char *line);
void                            hist_lst_add_next(t_hist *hist, char *line);
void                            hist_print(t_hist *hist);
t_hist                          *hist_free(t_hist *hist);
void                            hist_save_file(t_hist *s_hist);
t_hist                          *hist_remap_index(t_hist *hist);
t_hist                          *hist_delete_index(t_hist *hist, int index);
#endif
