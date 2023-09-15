# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/09/14 14:44:26 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_NAME =	main.c \
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
PREFIX = ./srcs/
SRCS = $(addprefix $(PREFIX), $(SRCS_NAME))
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = push_swap
BONUS = checker
BONUS_SRCS =	./bonus/main_bonus.c \
				./bonus/get_next_line_bonus.c \
				./bonus/get_next_line_utils_bonus.c\
				./bonus/parse.c \
				./bonus/commands.c \
				./bonus/init.c \
				./bonus/stk_commands.c \
				./bonus/clear_stacks.c \
				./bonus/move_chunks.c \
				./bonus/exec.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT = ft

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJS)
	cd libft; make; cd ..
	$(CC) $(OBJS) -Llibft -l$(LIBFT) -o $(NAME) -I $(HEADER)

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

$(BONUS) : $(BONUS_OBJS)
	cd libft; make; cd ..
	$(CC) $(BONUS_OBJS) -Llibft -l$(LIBFT) -o $(BONUS) -I $(HEADER) -g3

clean :
	cd libft; make clean; cd ..
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	cd libft; make fclean; cd ..
	rm -f $(NAME) $(BONUS)

re : fclean all


.PHONY : clean fclean re
