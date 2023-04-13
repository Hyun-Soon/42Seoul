# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/04/11 15:13:43 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
read_format.c \
check_char.c \
print_conversions1.c \
print_conversions2.c \

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
NAME = libftprintf.a

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS) $(BNS_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re
