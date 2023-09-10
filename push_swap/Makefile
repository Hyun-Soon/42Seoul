# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soon <soon@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/09/10 19:20:37 by soon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		parse.c \
		commands.c \
		hard_sort.c \
		init.c \
		stk_commands.c \
		print_result.c \
		clear_stacks.c \
		merge_to_a.c \
		merge_to_b.c \
		move_chunks.c \
		update_values.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -c -g3
HEADER = ./headers
NAME = push_swap
LIBFT = ft

all : $(NAME)

$(NAME) : $(OBJS)
	cd libft; make; cd ..
	$(CC) $(OBJS) -Llibft -l$(LIBFT) -o $(NAME) -I $(HEADER) #-g -fsanitize=address

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

clean :
	cd libft; make clean; cd ..
	rm -f $(OBJS)

fclean : clean
	cd libft; make fclean; cd ..
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re
