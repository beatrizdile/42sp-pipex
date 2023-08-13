# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:33:46 by bedos-sa          #+#    #+#              #
#    Updated: 2023/08/13 16:00:23 by bedos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
LIBFT = ./libft
RM = rm -f
FILES = srcs/pipex.c \
		srcs/pipex_utils.c
FILES_BONUS = bonus/pipex_bonus.c \
			  bonus/pipex_utils_bonus.c \
			  bonus/pipex_dups.c
OBJS = $(FILES:.c=.o)
OBJS_BONUS = $(FILES_BONUS:.c=.o)
green = \033[32m
reset = \033[0m

all: $(NAME)
	@echo "$(green)SUCCESS!!!$(reset)"

%.o: %.c
	@$(CC) $(CFLAGS) -I./include -c $< -o $@

$(NAME): $(OBJS)
ifneq ($(wildcard $(OBJS_BONUS)),)
	$(RM) $(OBJS_BONUS)
endif
	make -C $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT)/libft.a -O3 -g3 -L -lft -o $(NAME)

bonus: $(NAME)
ifneq ($(wildcard $(OBJS)),)
	$(RM) $(OBJS)
endif
	make FILES="$(FILES_BONUS)"

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME) $(NAME)

re: fclean all

run: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex_bonus input.txt "grep 42" "grep sil" "grep b" "grep bia" output.txt

.PHONY: all clean fclean re bonus
