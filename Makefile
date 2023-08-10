# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:33:46 by bedos-sa          #+#    #+#              #
#    Updated: 2023/08/10 11:02:21 by bedos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
LIBFT = ./libft
RM = rm -f
FILES = srcs/pipex.c \
		srcs/pipex_utils.c
OBJS = $(FILES:.c=.o)
green = \033[32m
reset = \033[0m

all: $(NAME)
	@echo "$(green)SUCCESS!!!$(reset)"

%.o: %.c include/pipex.h
	@$(CC) $(CFLAGS) -I./include -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT)/libft.a -O3 -g3 -L -lft -o $(NAME)

bonus: all

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

run: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex input.txt "grep 42" "grep sil" output.txt

.PHONY: all clean fclean re bonus
