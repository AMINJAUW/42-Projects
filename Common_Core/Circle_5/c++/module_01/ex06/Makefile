# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 14:16:58 by aminjauw          #+#    #+#              #
#    Updated: 2023/06/27 14:06:55 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	complain_filter

# BONUS_NAME		=	checker
#-------------------PATH-----------------------------

SOURCES			=	

BONUS_PWD		=

HEADER_PWD		=	

BONUS_HEADER_PWD=

# MLX_PATH		=	mlx/libmlx.a
#-------------------COMPILATION----------------------

# CC				=	c
CC				=	c++
# FLAGS			=	-Wall -Werror -Wextra
FLAGS			=	-Wall -Werror -Wextra -std=c++98
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address
# FLAGS			=	-Wall -Werror -Wextra -pthread 
# FLAGS			=	-Wall -Wextra -Werror -pthread
# LINK_FLAGS		=	-fsanitize=thread
# LINK_FLAGS		=	-Lmlx -lmlx  -framework OpenGL -framework AppKit $(MLX_PATH)

#-------------------SOURCES FILES----------------------
HEADERS			=

# BONUS_HEADERS 	=	

SRCS			=	$(SOURCES)Harl.cpp \
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
#	@make bonus -C libft/
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(LINK_FLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"


# bonus: $(OBJS) $(BONUS_OBJ)
# 	@make bonus -C libft/
# 	@printf "$(GREEN)Linking $(BONUS_NAME)... %45s\r$(NO_COLOR)" " "
# 	@$(CC) $(FLAGS) $(OBJS) $(BONUS_OBJ) libft/libft.a -o $(BONUS_NAME)
# 	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"
	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
#	@make clean -C libft/
	@rm -rf $(OBJS) $(BONUS_OBJ) $(MAIN_OBJ)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
#	@make fclean -C libft/
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

# rebonus : fclean bonus

test :
	@make
	@./$(NAME)

.PHONY: all clean fclean bonus re test