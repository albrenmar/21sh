# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by alsomvil          #+#    #+#              #
#    Updated: 2018/09/13 16:17:27 by alsomvil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c \
	  ft_apply.c \
	  ft_conversion.c \
	  ft_convertpxou.c \
	  ft_convertp.c \
	  ft_removestruct.c \
	  ft_convertdi.c \
	  ft_putstr_minu.c \
	  ft_applyoptiond.c \
	  ft_applyoptiono.c \
	  ft_applyoptionx.c \
	  ft_printuni.c \
	  ft_converts.c \
	  ft_checkoptionchart.c \
	  ft_convertpourcent.c \
	  ft_printuni_two.c \
	  ft_converts_one.c \
	  ft_atoi.c \
	  ft_itoabase.c \
	  ft_memdel.c \
	  ft_putchar.c \
	  ft_putchar_return.c \
	  ft_putstr_return.c \
	  ft_strdup.c \
	  ft_strlen.c \
	  ft_strndup.c \
	  ft_memalloc.c \
	  ft_strrev.c \
	  ft_bzero.c \
	  ft_strjoin.c \
	  ft_strsub.c \
	  ft_memset.c \
	  fdprintf.c \

OBJ = $(SRC:.c=.o)
CC = gcc -g
FLAGS = -Wall -Wextra -Werror
NAME = ftprintf.a

all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc $(FLAGS) -c -I. $^ -o $@

clean :
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re norme
