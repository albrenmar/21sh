# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by alsomvil          #+#    #+#              #
#    Updated: 2018/12/11 15:21:18 by bsiche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/main.c \
	  srcs/42sh/apply_cmd.c \
	  srcs/42sh/ft_create_tree.c \
	  srcs/42sh/ft_analize.c \
	  srcs/minishell/main_two.c \
	  srcs/minishell/apply_cmd.c \
	  srcs/minishell/buildin.c \
	  srcs/minishell/buildin_two.c \
	  srcs/minishell/duplicate_tab.c \
	  srcs/minishell/forfreetab.c \
	  srcs/minishell/get_info.c \
	  srcs/minishell/set_env.c \
	  srcs/minishell/set_env_two.c \
	  srcs/minishell/work_to_env.c \
	  srcs/Libft/ft_strcmp.c \
	  srcs/Libft/ft_split_whitespaces.c \
	  srcs/Libft/ft_strsplit.c \
	  srcs/GNL/term_setup.c \
	  srcs/GNL/stringsearch.c \
	  srcs/GNL/signals.c \
	  srcs/GNL/init_term.c \
	  srcs/GNL/cursor_pos.c \
	  srcs/GNL/cursor_check.c \
	  srcs/GNL/cursor_arrows.c \
	  srcs/GNL/term_size.c \
	  srcs/GNL/lib_utf.c \
	  srcs/GNL/print_line.c \
	  srcs/GNL/next_word.c \
	  srcs/GNL/cp_paste.c \
	  srcs/GNL/get_key.c


LIB    =   ./srcs/libft/
OBJ = $(SRC:.c=.o)
CC = gcc -g
FLAGS =  -Wall -Wextra -Werror
NAME = 42sh
_GREEN = $ \033[32m
_YELLOW = $ \033[33m
_YELLOW_S = $ \033[4;33m
_RED = $ \033[31m
_END = $ \033[0m


all : complib $(NAME)

$(NAME): $(OBJ)
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Compilation de printf:$(_END)" ; $(MAKE) -C srcs/ft_printf
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_GREEN) printf compiled [✓]$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Compilation de 42sh:$(_END)"
	@sleep 0.5
	@gcc $(CFLAGS) -g3 -o $(NAME) -I. -I./srcs/ft_printf $(OBJ) srcs/ft_printf/ftprintf.a srcs/libft/libft.a -ltermcap
	@echo "$(_YELLOW)|=>$(_END)$(_GREEN) 42sh compiled [✓]$(_END)"

%.o: %.c
	@$(CC) -c $(CFLAGS) -I. -I./ft_printf $< -o $@

clean:
	@$(MAKE) clean -C srcs/ft_printf
	@rm -f $(OBJ)
	@sleep 0.3
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Suppresion des fichiers objets (clean):$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_RED) ft_printf cleaned $(_END)$(_GREEN)[✓]$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_RED) 42sh cleaned $(_END)$(_GREEN)[✓]$(_END)"

complib :
			@echo -e "$(CLEAR_LINE)$(COL_BLUE)building lib$(COL_END)"
			@make -C $(LIB)

fclean: clean
	@$(MAKE) fclean -C srcs/ft_printf
	@sleep 0.3
	@echo "$(_YELLOW)|$(END)"
	@sleep 0.3
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Suppresion de l'executable (fclean):$(_END)"
	@rm -f $(NAME)
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_RED) executable cleaned$(_END) $(_GREEN)[✓]$(_END)"
	@echo "$(_YELLOW)|$(END)"

re: fclean all

.PHONY: ft_printf clean fclean all re
