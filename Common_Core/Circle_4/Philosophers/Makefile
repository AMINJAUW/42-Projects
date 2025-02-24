# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 14:16:58 by aminjauw          #+#    #+#              #
#    Updated: 2025/02/24 20:23:39 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

#-------------------PATH-----------------------------

SRC_DIR			= src/

OBJ_DIR			= .obj/

#-------------------COMPILATION----------------------

CC				=	cc
# FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address
FLAGS			=	-Wall -Werror -Wextra -pthread

#-------------------SOURCES FILES----------------------
SRC				=	main.c \
					ft_atoi.c \
					init.c \
					threads.c \
					utils.c \
					reapers.c

				
#-------------------OBJECTS----------------------

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o)) 

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

NO_COLOR		=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(NO_COLOR)" $@
	@$(CC) $(FLAGS) -Iinc -c $< -o $@

$(OBJ_DIR):
	@mkdir -p .obj

$(NAME): $(OBJ_DIR) $(OBJ)
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"

clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@rm -f $(NAME)

re: fclean all

test :
	@make
	@./$(NAME)

.PHONY: all clean fclean bonus re test