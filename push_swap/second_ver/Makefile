# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/09/04 21:00:32 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		parse.c \
		commands.c \
		hard_sort.c \
		init1.c \
		init2.c \
		stk_commands.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -c -g3
HEADER = ./headers
NAME = a.out
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
