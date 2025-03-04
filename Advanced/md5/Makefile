# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 18:49:16 by aminjauw          #+#    #+#              #
#    Updated: 2025/03/04 12:58:55 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	ft_ssl

#-------------------PATH-----------------------------

INCLUDE				=	inc/

OBJ_DIR				=	.obj/

MAIN_DIR			=	src/

COMMANDS_DIR		=	commands/

MESSAGE_DIGEST_DIR	=	message_digest/

ERROR_MANAGMENT_DIR	=	error_managment/

HASHTABLE_DIR		=	hashtable/

INIT_DIR			=	init/

UTILS_DIR			=	utils/

#-------------------COMPILATION----------------------

CC					=	cc
# FLAGS				=	-Wall -Werror -Wextra
FLAGS				=	-Wall -Werror -Wextra -g
# FLAGS				=	-Wall -Werror -Wextra -fsanitize=address -g

#-------------------SOURCES FILES----------------------

MAIN				=	main.c

MESSAGE_DIGEST		=	md5.c\
						print_result.c\
						MD_commands.c\
						convert_to_hex.c\
						create_matrix.c\
						read_inputs.c\
						sha256.c

COMMANDS			=	$(addprefix $(MESSAGE_DIGEST_DIR), $(MESSAGE_DIGEST))

ERROR_MANAGMENT		=	error_print.c

HASHTABLE			=	hashtable_allocation.c\
						hashtable_getters.c\
						hashtable_iterators.c\
						hashtable_setters.c

INIT				=	struct_init.c

UTILS				=	utils.c
				
SRC 				=   $(MAIN) \
						$(addprefix $(COMMANDS_DIR), $(COMMANDS)) \
						$(addprefix $(ERROR_MANAGMENT_DIR), $(ERROR_MANAGMENT)) \
						$(addprefix $(HASHTABLE_DIR), $(HASHTABLE)) \
						$(addprefix $(INIT_DIR), $(INIT)) \
						$(addprefix $(UTILS_DIR), $(UTILS))


#-------------------OBJECTS----------------------

OBJS				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#-------------------COLORS-----------------------

RED					=	\e[0;31m

YELLOW				=	\e[0;33m

GREEN				=	\e[0;32m

WHITE				=	\e[0;0m

BOLD				= 	\e[0;1m

BOLD_OFF			=	\e[0;21m


#-------------------RULES-----------------------
all:	$(NAME)

$(OBJ_DIR)%.o: $(MAIN_DIR)%.c
	@mkdir -p $(@D)
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(WHITE)" $@
	@$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $@ 


$(NAME):	$(OBJS)
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(WHITE)" " "
	@$(CC) -I $(INCLUDE) $(FLAGS) $(OBJS) -o $(NAME)
	@printf "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(WHITE)\n"
	
clean:
	@printf "$(RED)Deleting minishell objects...$(WHITE)\n"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@printf "$(RED)Deleting minishell executable...$(WHITE)\n"
	@rm -f $(NAME)

re: fclean all

test :
	@make re
	@./$(NAME)
	
.PHONY: all clean fclean bonus re test