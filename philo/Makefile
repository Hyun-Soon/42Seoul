# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 13:47:23 by hyuim             #+#    #+#              #
#    Updated: 2023/11/24 13:35:19 by hyuim            ###   ########.fr        #
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
CC = cc #-g3 #-g -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = philo
#BONUS = checker
#BONUS_SRCS =

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

#bonus : $(BONUS)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I $(HEADER) #-fsanitize=address

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

#$(BONUS) : $(BONUS_OBJS)
#	$(CC) $(BONUS_OBJS) -Llibft -l$(LIBFT) -o $(BONUS) -I $(HEADER) -g3

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re
