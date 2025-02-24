CC = cc
CCFLAGS = -Wall -Werror -Wextra

SRC_DIR = src/
OBJ_DIR = .obj/

SRC = ft_printf_csp100.c ft_printf_idu.c ft_printf_xX.c \
	print_format.c printf.c libft/ft_isdigit.c \
	libft/ft_atoi.c libft/ft_strlen.c libft/ft_itoa.c \
	libft/ft_strjoin.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

NAME = libftprintf.a

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "compiling $<"
	@$(CC) $(CCFLAGS) -c -I inc $< -o $@

$(NAME) : $(OBJ_DIR) $(OBJ)
	@echo "linking files"
	@ar -rcs $(NAME) $(OBJ)
	@echo "Done !"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/libft

bonus : all

clean :
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re : fclean all 

test : all
	@echo "\n\nTESTING :"
	@$(CC) $(CCFLAGS) main.c $(NAME)
	@./a.out

testc : all
	@echo "\n\nTESTING :"
	@$(CC) $(CCFLAGS) main.c $(NAME)
	@./a.out |cat -e

.PHONY: all clean fclean re 