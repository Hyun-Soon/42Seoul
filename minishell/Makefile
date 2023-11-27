# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 15:14:10 by hyuim             #+#    #+#              #
#    Updated: 2023/11/23 13:09:49 by hyuim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC_SRCS_NAME =	main.c \
			search_tree.c \
			init.c \
			here_doc.c \
			builtins.c \
			check_before_exec.c \
			free_tree.c \
			free_bundle.c \
			redirection.c \
			base_redir.c \
			handle_error.c \
			handle_envp.c \
			signal_handler.c \
			execution.c \
			setting.c \
			heredoc_signal_handler.c \
			write_to_tempfile.c \
			errs_in_builtin.c \
			support_builtin.c \
			builtins_part2.c

PARSE_SRCS_NAME = syntax_analysis.c \
				make_tree.c \
				tokenize_no_space.c \
				new_expansion.c \
				delete_quote.c \
				make_nodes.c \
				check_condition.c \
				handle_dollar_sign.c \
				handle_quote.c \
				handle_env.c \
				tokenizer.c

EXEC_OBJS = $(EXEC_SRCS:.c=.o)
PARSE_OBJS = $(PARSE_SRCS:.c=.o)
EXEC_PREFIX = ./srcs/exec/
PARSE_PREFIX = ./srcs/parse/
EXEC_SRCS = $(addprefix $(EXEC_PREFIX), $(EXEC_SRCS_NAME))
PARSE_SRCS = $(addprefix $(PARSE_PREFIX), $(PARSE_SRCS_NAME))
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
HEADER = ./headers
NAME = minishell

LIBFT = ft

all : $(NAME)


$(NAME) : $(EXEC_OBJS) $(PARSE_OBJS)
	cd libft; make; cd ..
	$(CC) $(EXEC_OBJS) $(PARSE_OBJS) -Llibft -l$(LIBFT) -L/usr/local/include/readline -lreadline -o $(NAME) -I $(HEADER) #-g3 -fsanitize=address

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(HEADER)

clean :
	cd libft; make clean; cd ..
	rm -f $(EXEC_OBJS) $(PARSE_OBJS)

fclean : clean
	cd libft; make fclean; cd ..
	rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re