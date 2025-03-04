/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:27:24 by aminjauw          #+#    #+#             */
/*   Updated: 2024/12/09 11:40:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hashtable *get_available_commands(void) {
    t_hashtable *commands_hashtable = ht_create();
    if (commands_hashtable == NULL)
        return alloc_err();
    t_status cmd_creation_status = SUCCESS;
    INIT_ALL_COMMANDS();
    if (cmd_creation_status == FAIL){
        ht_free_values(commands_hashtable);
        ht_destroy(commands_hashtable);
    }

    return commands_hashtable;
}

static bool valid_option(const char **options, char *str) {
    int i = 0;
    while (options[i] != NULL) {
        if (is_equal(options[i], str)) {
            return true;
        }
        i++;
    }
    return false;
}

static t_status init_options(t_command_line *command_line, const char **options) {
    
    
    void **value_pointers = ft_calloc(array_size(options), sizeof(void *));
    if (value_pointers == NULL)
        return FAIL;    
    for (int i = 0; options[i] != NULL; i++) {
        value_pointers[i] = ft_calloc(1, sizeof(bool));
        if (value_pointers[i] == NULL) {
            for (int j = 0; j < i; j++) {
                ft_free(value_pointers[j]);
            }
            ft_free(value_pointers);
            return FAIL;
        }
    }
    command_line->options = ht_create();
    if (command_line->options == NULL){
        for (int i = 0; options[i] != NULL; i++)
            ft_free(value_pointers[i]);
        ft_free(value_pointers);
        return FAIL;
    }
    for (size_t i = 0; options[i]; i++) {
        if (ht_set(command_line->options, options[i], value_pointers[i]) == NULL)
        {
            ht_destroy(command_line->options);
            for (int i = 0; options[i] != NULL; i++)
                ft_free(value_pointers[i]);
            ft_free(value_pointers);
            return FAIL;                  
        }
    }
    ft_free(value_pointers);
    return SUCCESS;
}

static t_status add_options(t_command_line *command_line, char **argv, int *i) {
    const char *options[] = {"-p", "-q", "-r", "-s", NULL};

    if (init_options(command_line, options) == FAIL)
        return FAIL;

    while (argv[*i] != NULL) {
        if (valid_option(options, argv[*i])) {
            //Case where there is a option already given the next time it will be considerd as a file
            if (*((bool *)ht_get(command_line->options, argv[*i]))) {
                return SUCCESS;
            }
            *((bool *)ht_get(command_line->options, argv[*i])) = true;
            *i += 1;
        } else {
            return SUCCESS;
        }
    }
    return SUCCESS;
}

static t_status add_files(t_command_line *command_line,int argc, char **argv, int i) {
    command_line->files = ft_calloc(argc - i + 1, sizeof(char *));
    if (command_line->files == NULL)
        return FAIL;
    int j = 0;
    while (i < argc) {
        command_line->files[j] = argv[i];
        i++;
        j++;
    }
    command_line->files[j] = NULL;
    return SUCCESS;
}

t_command_line *get_command_line_struct(t_command_line *command_line, int argc, char **argv) {

    command_line->command = argv[1];
    command_line->input_str = NULL;
    command_line->files = NULL;
    command_line->options = NULL;

    int i = 2;
    if (add_options(command_line, argv, &i) == FAIL)
        return alloc_err();
    if (i < argc) {
        if (add_files(command_line, argc, argv, i) == FAIL) {
            ht_free_values(command_line->options);
            ht_destroy(command_line->options);
            return alloc_err();
        }
    }
    return command_line;
}

