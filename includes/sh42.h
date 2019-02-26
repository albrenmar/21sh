/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 16:30:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/02/25 16:14:31 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H
# include "libft.h"
# include "ft_ls.h"
# include "minishell.h"
# include "expansions.h"
# include "set.h"
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

typedef struct	s_tree
{
	int			type;
	char		*cmd;
	t_last		*list_cmd;
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*prev;
}				t_tree;

typedef struct	s_set_fd
{
	int		STDIN;
	int		STDOUT;
	int		STDERR;
	int		three;
	int		four;
	int		five;
	int		six;
	int		seven;
	int		eight;
	int		nine;
}				t_set_fd;

typedef struct	s_shell
{
	t_lstcontainer	*alias_lst;
	t_lstcontainer	*env;
	t_hist			*hist;
	t_set_fd		*set_fd;
	t_env_set		*setenv_lst;
	char			**tab_env;
}				t_shell;

typedef struct		s_hash
{
    char			*binary;
	char			*path;
	int				totalhits;
    struct s_hash	*nextbinary;
}
					t_hash;

typedef struct	s_tracking
{
	char				**g_tab_exec;
	int					builtin;
	t_cursor			*pos;
	struct termios		default_term;
	struct termios		myterm;
	struct s_term_data	*terminfo;
	struct s_cpaste		*cpaste;
	struct s_auto		*aut;
	struct s_shell		*mysh;
	struct s_jobs		*jobs;
	struct s_hash		*hashtable[27];
	char				*str;
	char				*cmd;
	char				*comp;
	char				*prompt;
	t_lstcontainer		*key_list;
	int					swi;
	int					buffsize;
	int					histindex;
	int					histmax;
	int					interactive;
	int					lastreturn;
	int					sterminal;
	pid_t				spid;
	int					bg;
	int					fg;
	int					lastplace;
	// char				**orderhold;
}				t_tracking;

typedef struct	s_cmd
{
	int				status;
	struct s_cmd	*next;
	pid_t			cpid;
	int				done;
	int				stopped;
}				t_cmd;

typedef struct	s_jobs
{
	int				currentback;
	int				current;
	int				startback;
	struct s_jobs	*next;
	struct s_jobs	*prev;
	char			*name;
	char			wd[4096 + 1];
	int				stdin;
	int				stdout;
	int				stderr;
	int				place;
	int				background;
	pid_t			jpid;
	int				notified;
	int				backstart;
	struct termios	jterm;
	// pid_t			lastpid;
	struct s_cmd	*t_cmd;
}				t_jobs;

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


void			hist_file_to_lst(void);
int				print_hist();
int				get_last();
int				go_to(int i);
int				history_up(void);
int				history_down(void);
t_hist			*hist_lst_create(char *line);
void			hist_lst_add_next(t_hist *hist, char *line);
void			hist_print(t_hist *hist);
t_hist			*hist_free(t_hist *hist);
void			hist_save_file(t_hist *s_hist);
t_hist			*hist_remap_index(t_hist *hist);
t_hist			*hist_delete_index(t_hist *hist, int index);


t_last			*create_new_list(void);
t_last			*ft_parseur(char *line);
void			ft_lexeur(t_last *list_cmd);
void			tri_lexer(t_last *list_cmd);
void			ft_ast(t_last *list_command);
void			execute_ast(t_tree *tree, t_jobs *job);
int				exec_command(t_last *list, int foreground, t_jobs *job);
void			convert_list(t_last *list);
int				its_reddir(t_last *list);
int				its_fd_reddir(t_last *list);
int				its_reddir_to_fd(t_last *list);
int				its_pipe(t_last *list);
int				its_separator(t_last *list);
char			**create_tab_to_exec(t_last *list);
void			execute_pipe(char **tab_exec, t_jobs *job);
void			execute_two(char **tab_cmd);
void			execute_pipe_two(char **tab_exec, t_jobs *job);
char			**test_exist_fonction(char **tab_cmd);
int				error_lexer(t_last *list_cmd);
void			create_fich(t_last *list);
void			print_last(t_last *list);
int				its_eper(t_last *list);
int				is_builtin(void);
int				ft_exit(void);
int				is_builtin_alone(void);
int				ft_builtin_search(char *builtin);
int				builtin_exec(void);
void			jobs_builtin_output(t_jobs *tmp, int mode, int number, int options);
char			**tab_dup(char **tob);
int				jobs_builtin(void);
int				errors_fg(int nb, int error);
int				fg_builtin_output(t_jobs *tmp);


void			interactive_check_set_shell_group(void);
void			set_shell_signal_handlers(void);
void			set_process_signal_handlers(void);
t_cmd			*new_process(t_jobs *job, pid_t cpid);

void			continue_job(t_jobs *job, int foreground);
void			hash_binary(void);
int				hash_maker(const char *binary);
t_hash			*new_binary_hash(char *binary, char *path, int hits);
int				errors_hash(char *binary, int error);
int				ft_hash(void);
void			ft_hash_output(void);
int				empty_hash_table(void);
int				hash_update_commands(int j);
char			**tab_format_hash(char *binary);
char			**hashed_command(char **tab_exec);

t_jobs			*new_job(t_last *part, int background);
void			wait_for_job(t_jobs *job);
void			put_job_in_foreground(t_jobs *job, int cont);
void			put_job_in_background(t_jobs *job, int cont);
int				job_is_done(t_jobs *job);
int				job_is_stopped(t_jobs *job);
int				bg_builtin(void);
int				fg_builtin(void);
char			*parse_job_number(char *str);
int				job_exists(int place);
int				parse_job_sign(char *str);
int				errors_jobs(char option, int nb, int error);
int				errors_bg(int nb, int error);
int				cmd_checker(t_last *part, int mode, t_jobs *job);
void			free_last(t_last **cmd);
char			*check_separator(t_last *part);
int				suspended_jobs_count(void);
void			update_status(void);
int				update_process_status(pid_t pid, int status);
void			show_job_info(t_jobs *job, const char *status, int mode);
void			free_job(t_jobs *job);
void			jobs_notifications(void);
void			jobs_update_current(void);

char			**init_envp(t_lstcontainer *env);

#endif
