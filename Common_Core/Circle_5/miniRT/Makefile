# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 13:53:06 by vvalet            #+#    #+#              #
#    Updated: 2025/02/24 20:49:31 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	miniRT

#-------------------PATH-----------------------------

INCLUDE				=	include/

MAIN_DIR			=	src/

PARSING_DIR			=	parsing/

WINDOW_MGMT_DIR		=	window_mgmt/

VECTOR_MATH_DIR		=	vector_math/

UPDATE_IMG_DIR		=	update_image/

OBJECTS_MANIP_DIR	=	objects_manipulation/

#-------------------COMPILATION----------------------

CC					=	cc
# OBJ_FLAGS			=	-Wall -Werror -Wextra -g -Imlx
OBJ_FLAGS			=	-Wall -Werror -Wextra -Imlx

LINK_FLAGS			=	-Lmlx/ mlx/libmlx.a libft/libft.a -framework OpenGL -framework AppKit

#-------------------SOURCES FILES----------------------

MAIN				=	main.c\
						quit.c\
						utils_1.c\
						utils_2.c

PARSING				=	add.c\
						choose_fct.c\
						create_cam.c\
						create_al.c\
						create_sl.c\
						create_sphere.c\
						create_plane.c\
						create_cylinder.c\
						file_verify.c\
						file_parse.c\
						parsing_error.c\
						verifyers_simples.c\
						verifyers_complex.c

WINDOW_MGMT			=	init_window.c\
						key_hooks.c\
						display_infos.c

VECTOR_MATH			=	vector_math.c\
						dot_and_cross_product.c\
						float_math.c

UPDATE_IMG			=	find_color.c\
						find_point_seen.c\
						calculate_color.c\
						calculate_color_utils.c\
						color_mgmt.c\
						color_mgmt_2.c\
						check_cylinder.c\
						check_plane_sphere.c\
						check_utils.c\
						is_on_obj.c\
						update_image_data.c\
						update_image_data_utils.c\
						update_image.c

OBJECTS_MANIP		=	selector.c\
						translate.c\
						rotate.c\
						vector_rotation.c\
						resize.c

ALL_SRC				=	$(addprefix $(MAIN_DIR), $(MAIN))\
						$(addprefix $(PARSING_DIR), $(PARSING))\
						$(addprefix $(WINDOW_MGMT_DIR), $(WINDOW_MGMT))\
						$(addprefix $(VECTOR_MATH_DIR), $(VECTOR_MATH))\
						$(addprefix $(UPDATE_IMG_DIR), $(UPDATE_IMG))\
						$(addprefix $(OBJECTS_MANIP_DIR), $(OBJECTS_MANIP))

#-------------------OBJECTS----------------------

OBJS			=	$(ALL_SRC:.c=.o) 

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

WHITE			=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

%.o: %.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(WHITE)" $@
	@$(CC) $(OBJ_FLAGS) -I$(INCLUDE) -c $< -o $@ 

$(NAME):	$(OBJS)
	@make -C libft/
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(WHITE)" " "
	@$(CC) -I$(INCLUDE) $(LINK_FLAGS) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(WHITE)"
	
clean:
	@echo "$(RED)Deleting $(NAME) objects...$(WHITE)"
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean:	clean
	@echo "$(RED)Deleting $(NAME) executable...$(WHITE)"
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

test :
	@make re
	@./$(NAME)
	
.PHONY: all clean fclean bonus re test