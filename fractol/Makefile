# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/06/28 22:58:57 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
burning_ship.c \
color.c \
julia.c \
keyboard.c \
mandelbrot.c \
mlx.c \
mouse.c \
move.c \
zoom.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = fractol
LIBFT = ft

all : $(NAME)

$(NAME) : $(OBJS)
	cd libft; make; cd ..
	$(CC) $(OBJS) -Llibft -l$(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -I $(HEADER)

%.o : %.c
	$(CC) $(CFLAGS) -Imlx $< -o $@ -I $(HEADER)

clean :
	cd libft; make clean; cd ..
	rm -f $(OBJS)

fclean : clean
	cd libft; make fclean; cd ..
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re
