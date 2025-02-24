NAME		=	webserv

#------------------------------------PATH--------------------------------------

OBJ_PATH			=	objs/

INCS_PATH			=	inc/

PATHS		 		=	src/Initialisation_and_Configuration/ \
						src/Main_and_Utils/ \
						src/Request_and_cgi/ \
						src/Server/

#---------------------------------COMPILATION----------------------------------

CC			= 	c++

FLAGS		=	-g -Wall -Wextra -Werror -std=c++98 -I${INCS_PATH}

#---------------------------------SOURCE FILES---------------------------------

INIT_CONF	=	Cluster.cpp \
				Env.cpp \
				LocationConfig.cpp \
				ServerConfig_default_values.cpp \
				ServerConfig.cpp 

MAIN_UTILS	=	main.cpp \
				utils_default_message.cpp \
				utils_files.cpp \
				utils_strings.cpp \
				utils_others.cpp 

REQUEST_cgi	=	CGI_handler.cpp \
				Request_chunked.cpp \
				Request.cpp

SERVER		=	Server_cgi_utils.cpp \
				Server_cgi_operations.cpp \
				Server_operations.cpp \
				Server_request_handling.cpp \
				Server_response_autoindex.cpp \
				Server_response_content_type.cpp \
				Server_response_error.cpp \
				Server_response_methods.cpp \
				Server_utils_pfds.cpp \
				Server_utils_url.cpp \
				Server.cpp

ALL_SRCS 	=	$(addprefix $(word 1, $(PATHS)), $(INIT_CONF)) \
				$(addprefix $(word 2, $(PATHS)), $(MAIN_UTILS)) \
				$(addprefix $(word 3, $(PATHS)), $(REQUEST_cgi)) \
				$(addprefix $(word 4, $(PATHS)), $(SERVER))

#-----------------------------------OBJECTS------------------------------------

OBJS = $(addprefix ${OBJ_PATH}, $(ALL_SRCS:.cpp=.o))

#------------------------------------RULES-------------------------------------

all: ${NAME}

$(OBJ_PATH):
	@mkdir -p ${OBJ_PATH}
	@mkdir -p $(addprefix ${OBJ_PATH}, ${PATHS})

${OBJ_PATH}%.o: %.cpp
	@printf "Generating objects of ... %-45.45s\r" $(notdir $<)
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: $(OBJ_PATH) $(OBJS)
	@${CC} ${FLAGS} $(OBJS) -o ${NAME}

clean:
	@rm -Rf ${OBJ_PATH}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
