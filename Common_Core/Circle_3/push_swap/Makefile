# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 10:55:59 by aminjauw          #+#    #+#              #
#    Updated: 2025/02/24 17:22:10 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	push_swap

BONUS_NAME		=	checker
#-------------------PATH-----------------------------

SRC_DIR			=	src/
INC_DIR			=	inc/
OBJ_DIR			=	.obj/
#-------------------COMPILATION----------------------

CC				=	cc
FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address

#-------------------SOURCES FILES----------------------
INC			=	push_swap.h \
				ft_printf.h \
				libft.h

	
SRC				=	main_utils.c \
					init.c \
					init_str.c \
					ft_max.c \
					ft_min.c \
					func_p.c \
					func_s.c \
					func_r.c \
					func_rr.c \
					ft_calculate.c \
					ft_sort_utils.c \
					ft_sort_next.c \
					ft_sort_small.c \
					ft_sort_big.c
				
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
	@$(CC) $(FLAGS) -I inc/ -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	@make bonus -C src/libft/
	@$(CC) $(FLAGS) -I inc/ -c src/main.c -o .obj/main.o
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(FLAGS) $(OBJ) src/main.c src/libft/libft.a -I inc/ -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"


bonus: $(OBJ_DIR) $(OBJ)
	@make bonus -C src/libft/
	@$(CC) $(FLAGS) -I inc/ -c src/main_bonus.c -o .obj/main_bonus.o
	@printf "$(GREEN)Linking $(BONUS_NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(FLAGS) $(OBJ) src/main_bonus.c src/libft/libft.a -I inc/ -o $(BONUS_NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"
	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@make clean -C src/libft/
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@make fclean -C src/libft/
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

rebonus : fclean bonus

.PHONY: all clean fclean bonus re rebonus