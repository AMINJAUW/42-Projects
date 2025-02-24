CC = cc
CCFLAGS = -Wall -Werror -Wextra

HEADERS = libft.h ft_printf.h
INCLUDE_HEADERS =  $(addprefix( -include, $(HEADERS)))

SRC 	= 	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isalnum.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_printf_csp100.c \
			ft_printf_idu.c \
			ft_printf_xX.c \
			print_format.c \
			printf.c 




OBJ = $(SRC:.c=.o)

BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 
BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = libft.a

#-------------------COLORS-----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m

BOLD		= 	\x1b[1m

BOLD_OFF	=	\x1b[21m

all : $(NAME)

bonus : $(OBJ) $(BONUS_OBJ)
	@printf "$(YELLOW)Linking %-33.33s\r$(NO_COLOR)" $@
	@ar -rcs $(NAME) $(OBJ) $(BONUS_OBJ)

%.o : %.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-33.33s\r$(NO_COLOR)" $@
	@$(CC) $(CCFLAGS) -c$(INCLUDE_HEADERS) $< -o $@

$(NAME) : $(OBJ)
	@printf "$(YELLOW)Linking %-33.33s\r$(NO_COLOR)" $@
	@ar -rcs $(NAME) $(OBJ)

clean :
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re : fclean all 

.PHONY: all bonus clean fclean re 