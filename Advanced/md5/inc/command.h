/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:45:00 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/09 13:42:46 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "hashtable.h"


# define COMMAND_TYPES(X)    \
    X(STANDARD)              \
    X(MESSAGE_DIGEST)        \
    X(CIPHER)
	
# define STANDARD_COMMAND_LIST(X)   /* No commands in this type */

# define MESSAGE_DIGEST_COMMAND_LIST(X) \
    X(md5)                             \
    X(sha256)

void 	md5(u_int32_t **input_matrix, u_int32_t *hash_output);
void 	sha256(u_int32_t **input_matrix, u_int32_t *hash_output);

# define CIPHER_COMMAND_LIST(X)     /* No commands in this type */

// Generate enum for command types
# define GENERATE_ENUM(type) type,
typedef enum e_commands_type {
    COMMAND_TYPES(GENERATE_ENUM)
} t_commands_type;

// Struct for function pointer and type type
typedef struct s_function_pointer {
    void *pointer;
    t_commands_type type;
} t_function_pointer;

// Macro to initialize each command with its type type
# define INIT_COMMAND_WITH_TYPE(command) \
    do {  \
        t_function_pointer *cmd_data = ft_calloc(1, sizeof(t_function_pointer));\
        if (!cmd_data) {  \
			cmd_creation_status = FAIL; \
			break; \
		} \
        cmd_data->pointer = (void *)&command; \
        cmd_data->type = cmd_type;  \
        if (ht_set(commands_hashtable, #command, cmd_data) == NULL){ \
			ft_free(cmd_data); \
			cmd_creation_status = FAIL;	\
		}\
		cmd_creation_status = SUCCESS; \
    } while (0);

// Macro to initialize a whole command type list with a specific type type
# define INIT_COMMAND_TYPE(list_macro) \
		if (cmd_creation_status != FAIL)\
		{ \
			list_macro(INIT_COMMAND_WITH_TYPE);\
		}


// Macro to iterate over each type and initialize it
# define GENERATE_INIT_TYPE(type) \
	cmd_type = type; \
    INIT_COMMAND_TYPE(type##_COMMAND_LIST)

# define FOREACH_COMMAND_TYPE() \
	do { \
		t_commands_type cmd_type;\
    	COMMAND_TYPES(GENERATE_INIT_TYPE)\
	} while (0)

# define INIT_ALL_COMMANDS() FOREACH_COMMAND_TYPE()


#endif
