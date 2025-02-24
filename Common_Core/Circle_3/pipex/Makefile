# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 13:18:51 by aminjauw          #+#    #+#              #
#    Updated: 2025/02/24 16:35:41 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

# BONUS_NAME		=	checker
#-------------------PATH-----------------------------

SRC_DIR			= src/

OBJ_DIR			= .obj/

HEADER_DIR		= inc/

BONUS_HEADER_DIR=

# MLX_PATH		=	mlx/libmlx.a
#-------------------COMPILATION----------------------

CC				=	cc
FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address
# FLAGS			=	-Wall -Wextra -Werror -Imlx  -g
# LINK_FLAGS		=	-Lmlx -lmlx  -framework OpenGL -framework AppKit $(MLX_PATH)

#-------------------SOURCES FILES----------------------
HEADERS			=	pipex.h

# BONUS_HEADERS 	=	

SRC			=	main.c \
				parsing.c \
				parsing_next.c \
				parsing_next_utils.c \
				utils.c

# BONUS_SRC		=	$(BONUS_DIR)main_bonus.c
				
#-------------------OBJECTS----------------------

OBJ			=		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

NO_COLOR		=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(NO_COLOR)" $@
	@$(CC) $(FLAGS) $(I_HEADER) $(I_BONUS_HEADER) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@make bonus -C src/libft/
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(LINK_FLAGS) $(OBJ) src/libft/libft.a -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"
	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@make clean -C src/libft/
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@make fclean -C src/libft/
	@rm -f $(NAME)
re: fclean all

test :
	@make
	@./$(NAME)

.PHONY: all clean fclean bonus re rebonus