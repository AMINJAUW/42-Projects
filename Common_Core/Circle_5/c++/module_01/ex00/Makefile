# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 14:16:58 by aminjauw          #+#    #+#              #
#    Updated: 2023/11/19 15:11:32 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Zombie

#-------------------PATH-----------------------------

SOURCES			=	

HEADER_PWD		=	

#-------------------COMPILATION----------------------

CC				=	c++
# FLAGS			=	-Wall -Werror -Wextra
FLAGS			=	-Wall -Werror -Wextra -std=c++98
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address

#-------------------SOURCES FILES----------------------
HEADERS			=

# BONUS_HEADERS 	=	

SRCS			=	$(SOURCES)Zombie.cpp\
					$(SOURCES)newZombie.cpp\
					$(SOURCES)randomChump.cpp\
					$(SOURCES)main.cpp

				
# BONUS_SRC		=	$(BONUS_PWD)main_bonus.c
				
#-------------------OBJECTS----------------------

OBJS			=	$(SRCS:.cpp=.o) 

BONUS_OBJ		=	$(BONUS_SRC:.cpp=.o)

MAIN_OBJ		=	$(MAIN:.cpp=.o)

#-------------------HEADERS----------------------

I_HEADER		=	$(addprefix( -include, $(HEADERS)))

I_BONUS_HEADER	=	$(addprefix( -include, $(BONUS_HEADERS)))

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

NO_COLOR		=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

%.o: %.cpp
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(NO_COLOR)" $@
	@$(CC) $(FLAGS) $(I_HEADER) $(I_BONUS_HEADER) -c $< -o $@

$(NAME):	$(OBJS) $(MAIN_OBJ)
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(LINK_FLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"


	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@rm -rf $(OBJS) $(BONUS_OBJ) $(MAIN_OBJ)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

test :
	@make
	@./$(NAME)

.PHONY: all clean fclean re test