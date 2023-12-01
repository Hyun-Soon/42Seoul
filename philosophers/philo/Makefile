# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 13:47:23 by hyuim             #+#    #+#              #
#    Updated: 2023/12/01 16:48:17 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_NAME =	main.c \
			init.c \
			str_utils.c \
			time_utils.c \
			philo_fork_behavior.c \
			philo_behavior.c \
			free_and_destroy.c \
			thread_utils.c

OBJS = $(SRCS:.c=.o)
PREFIX = ./srcs/
SRCS = $(addprefix $(PREFIX), $(SRCS_NAME))
CC = cc #-fsanitize=thread#-g3
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I $(HEADER)

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re