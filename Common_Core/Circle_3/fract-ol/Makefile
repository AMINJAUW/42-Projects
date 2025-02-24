# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 13:18:51 by aminjauw          #+#    #+#              #
#    Updated: 2025/02/24 17:37:41 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fract-ol

# BONUS_NAME		=	checker
#-------------------PATH-----------------------------

SRC_DIR			=	src/
INC_DIR			=	inc/
OBJ_DIR			=	.obj/

MLX_PATH		=	src/mlx/libmlx.a
#-------------------COMPILATION----------------------

CC				=	gcc
# FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address
FLAGS			=	-Wall -Wextra -Werror -Isrc/mlx  -g
LINK_FLAGS		=	-Lsrc/mlx/ -framework OpenGL -framework AppKit $(MLX_PATH)

#-------------------SOURCES FILES----------------------
	
SRC				=	main.c \
					update_img.c \
					colors.c \
					complex.c \
					mandelbrot.c \
					julia.c \
					fractal_colors.c \
					window.c \
					window_2.c 
					
				
#-------------------OBJECTS----------------------

OBJ			=	$(addprefix	$(OBJ_DIR), $(SRC:.c=.o))


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
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@make bonus -C src/libft/
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(LINK_FLAGS) $(OBJ) src/libft/libft.a -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"
	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
# @make clean -C src/libft/
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
# @make fclean -C src/libft/
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re 