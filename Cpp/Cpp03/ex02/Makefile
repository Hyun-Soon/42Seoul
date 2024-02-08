#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

SRCS_NAME =	main.cpp \
			ClapTrap.cpp \
			ScavTrap.cpp \
			FragTrap.cpp
PREFIX = ./srcs/
SRCS = $(addprefix $(PREFIX), $(SRCS_NAME))
OBJS = $(SRCS:.cpp=.o)
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -c
HEADER = ./includes
NAME = FragTrap

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -I $(HEADER)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	@echo $(YELLOW)"                    Cpp is ready"$(EOC)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	
%.o : %.cpp
	@$(CC) $(CXXFLAGS) $< -o $@ -I $(HEADER)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


.PHONY : clean fclean re
