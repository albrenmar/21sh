# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by alsomvil          #+#    #+#              #
#    Updated: 2018/10/25 14:43:42 by alsomvil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  main_two.c \
	  buildin.c \
	  buildin_two.c \
	  duplicate_tab.c \
	  forfreetab.c \
	  get_info.c \
	  set_env.c \
	  set_env_two.c \
	  work_to_env.c \
	  srcs/ft_strcmp.c \
	  srcs/ft_split_whitespaces.c \
	  srcs/ft_strsplit.c \
	  get_next_line.c \
	  ft_analize.c \

OBJ = $(SRC:.c=.o)
CC = gcc -g
FLAGS =  -Wall -Wextra -Werror
NAME = minishell
_GREEN = $ \033[32m
_YELLOW = $ \033[33m
_YELLOW_S = $ \033[4;33m
_RED = $ \033[31m
_END = $ \033[0m


all : $(NAME)

$(NAME): $(OBJ)
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Compilation de printf:$(_END)" ; $(MAKE) -C ft_printf
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_GREEN) printf compiled [✓]$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Compilation de minishell:$(_END)"
	@sleep 0.5
	@gcc $(CFLAGS) -g3 -o $(NAME) -I. -I./ft_printf $(OBJ) ft_printf/ftprintf.a
	@echo "$(_YELLOW)|=>$(_END)$(_GREEN) minishell compiled [✓]$(_END)"

%.o: %.c
	@$(CC) -c $(CFLAGS) -I. -I./ft_printf $< -o $@

clean:
	@$(MAKE) clean -C ft_printf
	@rm -f $(OBJ)
	@sleep 0.3
	@echo "$(_YELLOW)|==>$(_END)$(_YELLOW_S)Suppresion des fichiers objets (clean):$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_RED) ft_printf cleaned $(_END)$(_GREEN)[✓]$(_END)"
	@sleep 0.3
	@echo "$(_YELLOW)|=>$(_END)$(_RED) minishell cleaned $(_END)$(_GREEN)[✓]$(_END)"

fclean: clean
	@$(MAKE) fclean -C ft_printf
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
