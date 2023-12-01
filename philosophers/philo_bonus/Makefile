# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 13:47:23 by hyuim             #+#    #+#              #
#    Updated: 2023/12/01 13:59:14 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_NAME =	main.c \
			sem_utils.c \
			time_utils.c \
			libft_funcs.c \
			handle_philo.c \
			philo_behavior.c \
			philo_fork_behavior.c \
			str_utils.c \
			fork_utils.c \
			monitoring.c

OBJS = $(SRCS:.c=.o)
PREFIX = ./srcs/
SRCS = $(addprefix $(PREFIX), $(SRCS_NAME))
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = philo_bonus


BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I $(HEADER) #-fsanitize=thread #-g3

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re
