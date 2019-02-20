# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by alsomvil          #+#    #+#              #
#    Updated: 2019/02/20 18:16:53 by alsomvil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=	42sh

SRC = main.c \
	  42sh/ft_parseur.c \
	  42sh/ft_lexeur.c \
	  42sh/ft_modif_list.c \
	  42sh/ft_ast.c \
	  42sh/its_token.c \
	  42sh/execute_ast.c \
	  42sh/execute_pipe.c \
	  42sh/add_path_to_bin.c \
	  42sh/create_tab_to_exec.c \
	  42sh/convert_list.c \
	  42sh/create_fich.c \
	  GNL/term_setup.c \
	  GNL/stringsearch.c \
	  GNL/signals.c \
	  GNL/init_term.c \
	  GNL/cursor_pos.c \
	  GNL/cursor_check.c \
	  GNL/cursor_arrows.c \
	  GNL/term_size.c \
	  GNL/lib_utf.c \
	  GNL/print_line.c \
	  GNL/next_word.c \
	  GNL/copy.c \
	  GNL/paste.c \
	  GNL/get_key.c \
	  auto_complete/auto_complete.c \
	  auto_complete/auto_complete_cleanup.c \
	  auto_complete/auto_complete_list.c \
	  auto_complete/auto_complete_page.c \
	  auto_complete/auto_complete_loop.c \
	  auto_complete/auto_complete_move.c \
	  auto_complete/auto_complete_parse.c \
	  auto_complete/auto_complete_padding.c \
	  auto_complete/auto_complete_type.c \
	  auto_complete/print_arg_list.c \
	  auto_complete/send_color.c \
	  auto_complete/var_list.c \
	  ft_ls/cmdparse.c \
	  ft_ls/cmdparse_misc.c \
	  ft_ls/color.c \
	  ft_ls/free_all.c \
	  ft_ls/print.c \
	  ft_ls/ft_clean.c \
	  ft_ls/ft_clean_bis.c \
	  ft_ls/ft_cleanusr.c \
	  ft_ls/ft_devid.c \
	  ft_ls/ft_ls.c \
	  ft_ls/getstat.c \
	  ft_ls/getusr.c \
	  ft_ls/info_to_str.c \
	  ft_ls/main_ls.c \
	  ft_ls/makelist.c \
	  ft_ls/mode.c \
	  ft_ls/mergesort.c \
	  ft_ls/path.c \
	  ft_ls/recursive.c \
	  ft_ls/sortoption.c \
	  ft_ls/termsize.c \
	  ft_ls/timesort.c \
	  alias/alias_bin.c \
	  alias/alias_file.c \
	  alias/alias_struct.c \
	  test/test_main.c \
	  test/test_two_arg.c \
	  test/test_three_arg.c \
	  shell_core/copyenv.c \
	  shell_core/env_to_lst.c \
	  shell_core/init_shell.c \
	  shell_core/get_pwd.c \
	  history/history_lst.c \
	  history/history_lst2.c \
	  history/history_lst_options.c \
	  history/history_loop.c \
	  history/print_hist.c

CLEAR_LINE	= \033[2K
BEGIN_LINE	= \033[A
COL_END		= \033[0m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_VIOLET	= \033[1;35m
COL_CYAN	= \033[1;36m
COL_WHITE	= \033[1;37m

OBJ = $(SRC:.c=.o)
SRCDIR = srcs
OBJDIR = obj
INCDIR = includes

PWD := $(shell pwd)

SRCP =		$(addprefix $(SRCDIR)/, $(SRC))
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR =	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB = ./srcs/libft
LIBADD = ./srcs/libft/libft.a

FLAG = -g -fsanitize=address

all : $(NAME)

$(NAME) : complib $(OBJP)
			@gcc $(FLAG) $(OBJP) -o $(NAME) -ltermcap -I $(INCDIR) $(LIBADD)
			@echo -e "$(CLEAR_LINE)$(COL_CYAN)All done $(COL_END)ᕦ(ò_óˇ)ᕤ"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) $< -o $@  -I $(INCDIR)
			@echo "$(CLEAR_LINE)$(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"
complib :
			@make -C $(LIB)
clean :
			@echo -e "$(CLEAR_LINE)$(COL_RED)Cleaning objs dir$(COL_END)"
			@rm -rf $(OBJDIR)
			@echo -e "$(CLEAR_LINE)$(COL_GREEN)Done ✓$(COL_END)"
			@echo -e "$(CLEAR_LINE)$(COL_RED)Cleaning lib dir$(COL_END)"
			@make clean -C $(LIB)
			@echo -e "$(CLEAR_LINE)$(COL_GREEN)Done ✓$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C $(LIB)


re :		fclean all

.PHONY: ft_printf clean fclean all re
