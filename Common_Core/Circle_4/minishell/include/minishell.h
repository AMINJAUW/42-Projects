/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:47:59 by aminjauw          #+#    #+#             */
/*   Updated: 2023/10/13 12:20:08 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "errno.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>

int	g_sig_flag;

# define WORD 0
# define PUNCT 1

# define SINGLE_LINE 2

# define AMBIGUOUS_REDIR "ambiguous redirect"
# define CMD_NOT_FOUND_STR "command not found"
# define DIRECTORY_STR "is a directory"
# define ENDING_CHEVRON_STR "syntax error near unexpected token `newline'"
# define EOF_TRAILING_PIPE "syntax error: unexpected end of file"
# define HOME_NOT_SET_STR "HOME not set"
# define NO_FILE_STR "No such file or directory"
# define NON_NUM_ARGS "numeric argument required"
# define ONLY_DOTS "filename argument required\
\n.: usage: . filename [arguments]"
# define PARENT_DIR_STR "error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"
# define PERMISSION_STR "Permission denied"
# define TOKEN_STR "syntax error near unexpected token"
# define TOO_MANY_ARGS "too many arguments"
# define WRONGID_STR "not a valid identifier"

/* To have some colors in your life :) */
# define RED "\x1b[31m"
# define WHI "\x1b[0m"

typedef enum e_error_codes
{
	SUCCES,
	FAIL,
	CONTINUE,
	CMD_NOT_FOUND = 127,
	TOKEN = 258,
}	t_error_codes;

typedef enum e_io_types
{
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
}	t_io_types;

typedef struct s_io
{
	int			type;
	char		*io;
	char		*exp_tab;
	char		*exp_io;
	char		**split_exp_io;
	int			open_mode;
	int			heredoc_read_end;
	int			is_env_var;
	int			is_in_quotes;
	struct s_io	*next;
}	t_io;

typedef struct s_cmd
{
	char			**command_line;
	t_io			*io;
	int				input_fd;
	int				output_fd;
	char			*cmd_path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data {
	char	**envp;
	char	*cwd;
	char	*oldcwd;
	int		saved_tty_fds[2];
	int		err_nbr;
	int		last_err;
	int		exit_flag;
	char	*line;
	char	*exp_tab;
	char	**lex_line;
	char	*lex_tab;
	t_cmd	*commands;
	char	*cur_cmd;
	int		trailing_pipe;
	char	**exec_path;
	char	*final_line;
}	t_data;

/* Environment: initialization & closing */
void	init_env(char **envp, t_data *data);
void	clear_data(t_data *data);
void	close_env(t_data *data);

/* Environment: signals */
int		check_line(t_data *data);
void	check_signal_exec(t_data *data);
void	sig_exec(int sig);
void	sigint_prompt(int sig);

/* Line management: expander */
int		env_var_exp(t_data *data);
int		chars_to_replace(char *string);
size_t	find_size(char *line, t_data *data);
int		is_io(char *line, int index);
int		ft_next_char(char *str, char c);
void	ft_itoa_copy(char *dest, int n);

/* Line management: lexer */
int		lexer(t_data *data);
int		line_cleaner(char *line, t_data *data);
int		check_quotes(char *line, int in_quotes);
int		is_sticked_couple_quotes(char *line, int i, t_data *data);
int		token_size(char *line, int pos, t_data *data);

/* Parser */
int		parser(t_data *data);
int		is_chevrons(t_data *data, int index);
int		is_pipe(t_data *data, int index);
int		index_of_nth_block(t_data *data, int command_block);
int		input_remaining(t_io *io);
int		mk_commands(t_data *data);
t_io	*mk_io(t_data *data, int command_block);

/* Parser: Finish_parsing */
int		finish_parsing(t_data *data);
int		complete_heredocs(t_cmd *commands, t_data *data);
int		close_heredocs_on_failure(t_data *data, t_io *io);
int		env_var_exp_heredoc(t_data *data, t_io *io);

/* Executer */
int		executer(t_data *data);
int		access_command(t_data *data, t_cmd *commands);
void	run_program(t_data *data, t_cmd *commands, int *end);
void	run_builtin(t_data *data, t_cmd *commands);
int		no_commands(t_data *data);
int		is_path_cmd(char *cmd);
int		is_builtin(char *cmd);
int		no_path(t_data *data);
void	find_builtin(char *cmd, int (**fct)(int, char**, t_data*));
size_t	find_size(char *line, t_data *data);
int		string_arr_empty(char **str);

/* Executer: IO files management */
int		handle_io_files(t_cmd *command, t_data *data);
int		io_lexer(t_io *io, t_data *data);
int		io_env_var_exp(t_io *io, t_data *data);
int		io_line_cleaner(char *line, t_data *data, t_io *io);
int		io_token_size(char *line, int pos, t_data *data);

/* Executer: IO FD management */
void	fd_management_builtin(t_cmd *command, t_data *data);
void	fd_management_input(t_cmd *command, int pipe_fd[2],
			t_data *data);
void	fd_management_output(t_cmd *command, int pipe_fd[2],
			t_data *data);

/* Builtins */
int		ft_cd(int argc, char **argv, t_data *data);
int		ft_echo(int argc, char **argv, t_data *data);
int		ft_env(int argc, char **argv, t_data *data);
int		ft_exit(int argc, char **argv, t_data *data);
int		ft_export(int argc, char **argv, t_data *data);
void	declare(int argc, char **envp);
int		ft_pwd(int argc, char **argv, t_data *data);
int		ft_unset(int argc, char **argv, t_data *data);

/* Builtins utils */
int		find_index(char *s, char **envp);
int		str_is_num(char *str);

/* Error Management */
int		io_file_error(int pipe_fd[2]);
void	fork_error(t_cmd *command, int pipe_fd[2], t_data *data);
int		ft_error(int err_code, char *token, char *str, t_data *data);
void	exit_child_process(int exit_nbr, t_data *data);

/* Chained list funcions */
void	io_free_all(t_io *start);
t_io	*io_add_back(t_io *start, char *io, t_data *data);
t_io	*io_last(t_io *start);
int		commands_add_back(t_data *data, char **command_line,
			int command_block);
void	commands_free_first(t_data *data);
t_cmd	*commands_last(t_cmd *start);

/* Utils */
void	ft_free(void **ptr);
void	close_fd_secure(int fd, t_data *data);
int		save_tty_fds(t_data *data);
int		restore_tty(t_data *data);

#endif
