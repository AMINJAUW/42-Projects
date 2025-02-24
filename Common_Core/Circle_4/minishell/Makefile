# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 18:49:16 by aminjauw          #+#    #+#              #
#    Updated: 2025/02/24 20:36:32 by aminjauw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

#-------------------PATH-----------------------------

INCLUDE				=	include/

MAIN_DIR			=	src/

LEXER_DIR			=	lexer/

PARSER_DIR			=	parser/

EXECUTER_DIR		=	executer/

BUILTINS_DIR		=	builtins/

FINISH_PARSING_DIR	=	finish_parsing/

IO_MGMT_DIR			=	io_mgmt/

ERROR_MANAGMENT_DIR	=	error_managment/

#-------------------COMPILATION----------------------

CC				=	cc
FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address -g

#-------------------SOURCES FILES----------------------

MAIN				=	env_mgmt.c\
						main.c\
						signals.c\
						save_tty.c\
						utils.c\

LEXER				=	env_var_expander.c\
						env_var_utils.c\
						lexer_utils.c\
						lexer.c\
						line_cleaner.c\
						line_cleaner_utils.c
						
PARSER				=	parser.c\
						mk_io.c\
						mk_commands.c\
						parser_utils.c\
						t_cmd_fcts.c\
						t_io_fcts.c

FINISH_PARSING		=	finish_parsing.c\
						heredoc.c\
						env_var_expander_heredoc.c

EXECUTER			=	executer.c\
						exec_errors.c\
						exec_utils.c\
						builtins_mgmt.c\
						access_cmd.c\
						child_processes.c
						
IO_MGMT				=	io_fd_mgmt.c\
						io_files_mgmt.c\
						io_env_var_expander.c\
						io_line_cleaner_utils.c\
						io_line_cleaner.c\
						io_lexer.c
						

BUILTINS			=	builtins_utils.c\
						echo.c\
						cd.c\
						pwd.c\
						export.c\
						export_declare.c\
						exit.c\
						unset.c\
						env.c

ERROR_MANAGMENT		=	error.c
				
ALL_SRC				=	$(addprefix $(MAIN_DIR), $(MAIN))\
						$(addprefix $(LEXER_DIR), $(LEXER))\
						$(addprefix $(PARSER_DIR), $(PARSER))\
						$(addprefix $(FINISH_PARSING_DIR), $(FINISH_PARSING))\
						$(addprefix $(EXECUTER_DIR), $(EXECUTER))\
						$(addprefix $(IO_MGMT_DIR), $(IO_MGMT))\
						$(addprefix $(BUILTINS_DIR), $(BUILTINS))\
						$(addprefix $(ERROR_MANAGMENT_DIR), $(ERROR_MANAGMENT))

#-------------------OBJECTS----------------------

OBJS			=	$(ALL_SRC:.c=.o) 

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

WHI				=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

%.o: %.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(WHI)" $@
	@$(CC) $(FLAGS) -I$(INCLUDE) -I/usr/local/opt/readline/include -c $< -o $@ 

$(NAME):	$(OBJS)
	@make -C libft/
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(WHI)" " "
	@$(CC) -I$(INCLUDE) $(FLAGS) $(OBJS) libft/libft.a -o $(NAME) -lreadline -L/usr/local/opt/readline/lib
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(WHI)"
	
clean:
	@echo "$(RED)Deleting minishell objects...$(WHI)"
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean:	clean
	@echo "$(RED)Deleting minishell executable...$(WHI)"
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

test :
	@make re
	@./$(NAME)
	
.PHONY: all clean fclean bonus re test