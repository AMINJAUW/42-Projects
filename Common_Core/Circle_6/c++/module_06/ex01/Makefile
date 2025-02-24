# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 14:16:58 by aminjauw          #+#    #+#              #
#    Updated: 2023/08/29 14:45:54 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Serialize


#-------------------COMPILATION----------------------

CC				=	c++
# FLAGS			=	-Wall -Werror -g -Wextra -std=c++98
FLAGS			=	-Wall -Werror -Wextra -std=c++98

#-------------------SOURCES FILES----------------------

SRCS			=	main.cpp\
					Serializer.cpp


#-------------------OBJECTS----------------------

OBJS			=	$(SRCS:.cpp=.o) 

BONUS_OBJ		=	$(BONUS_SRC:.cpp=.o)

MAIN_OBJ		=	$(MAIN:.cpp=.o)

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

.PHONY: all clean fclean bonus re test