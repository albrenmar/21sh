# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/25 18:18:05 by bsiche            #+#    #+#              #
#    Updated: 2018/12/03 02:59:16 by bsiche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAG = -Wall -Werror -Wextra

CC = gcc

#Directories

SRCDIR =	srcs
OBJDIR =	objs
INCDIR =	includes\

LIB    =    libft/

NAME = 42sh

SRC =	main.c \
		term_setup.c \
		stringsearch.c \
		signals.c \
		init_term.c \
		cursor_pos.c \
		cursor_check.c \
		cursor_arrows.c \
		term_size.c \
		lib_utf.c \
		print_line.c \
		next_word.c \
		get_key.c

OBJ = $(SRC:.c=.o)

LIBFT =	-Llibft/ -lft

OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCP =		$(foreach dir, $(INCDIR), -I$(dir))

CLEAR_LINE		= \033[2K
BEGIN_LINE		= \033[A
COL_END 		= \033[0m
COL_RED			= \033[1;31m
COL_GREEN		= \033[1;32m
COL_YELLOW		= \033[1;33m
COL_BLUE		= \033[1;34m
COL_VIOLET		= \033[1;35m
COL_CYAN		= \033[1;36m
COL_WHITE		= \033[1;37m


.PHONY: all clean fclean re

all : complib $(OBJDIR) $(NAME)

$(NAME): $(OBJP)
			@$(CC) -g $(CFLAGS) -o $@ $^ $(INCP) $(LIBFT) -ltermcap
			@echo -e "$(CLEAR_LINE)$(COL_CYAN)All done $(COL_END)ᕦ(ò_óˇ)ᕤ"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@echo -e "$(CLEAR_LINE)$(COL_VIOLET)$(NAME)$(COL_END)........................ $(COL_YELLOW)$<$(COL_END)$(BEGIN_LINE)"
			@$(CC) -g $(CFLAGS) -c -o $@ $^ $(INCP)

$(OBJDIR):
			@echo -e "$(CLEAR_LINE)$(COL_BLUE)building $(NAME)$(COL_END)"
			@mkdir -p $(OBJDIR)

complib :
			@echo -e "$(CLEAR_LINE)$(COL_BLUE)building lib$(COL_END)"
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