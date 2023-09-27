# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/09/27 20:07:33 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_NAME =	main.c \
			init.c \
			parse.c \
			exec.c \
			redirect.c

OBJS = $(SRCS:.c=.o)
PREFIX = ./srcs/
SRCS = $(addprefix $(PREFIX), $(SRCS_NAME))
CC = cc
CFLAGS = -Wall -Wextra -Werror -c -g3
HEADER = ./headers
NAME = pipex

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
