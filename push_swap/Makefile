# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/07/04 20:10:11 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		parse.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -c
HEADER = ./headers
NAME = a.out
LIBFT = ft

all : $(NAME)

$(NAME) : $(OBJS)
	cd libft; make; cd ..
	$(CC) $(OBJS) -Llibft -l$(LIBFT) -o $(NAME) -I $(HEADER)

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
