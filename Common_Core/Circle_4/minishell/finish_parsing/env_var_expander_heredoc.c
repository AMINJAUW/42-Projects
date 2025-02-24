/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expander_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:52 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/13 12:20:53 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a pointer to the value correponding to the variable name "variable".
Because of the '$', the "variable_size" is one char shorter than what needs to
be replaced, and the variable name begins at "variable[1]". The function
iterates through "datas->envp" and checks if one of the key corresponds to the
variable name. If so, it returns a pointer to the first char of that key (i.e.
the first character after the '='). */
static char	*find_value(char *variable, t_data *datas)
{
	int		i;
	int		variable_size;

	i = 0;
	variable_size = chars_to_replace(variable) - 1;
	variable++;
	while (datas->envp[i])
	{
		if (ft_strncmp(variable, datas->envp[i], variable_size) == 0
			&& datas->envp[i][variable_size] == '=')
			break ;
		i++;
	}
	if (datas->envp[i] && datas->envp[i][variable_size] == '=')
		return (&datas->envp[i][variable_size + 1]);
	else
		return (NULL);
}

/* If the char encountered is a '$' and at least one char needs to be replaced,
that function is called. Pos[0] is the position counter of "*line", pos[1] is
the position counter "new_line". If the next char is a '?', "datas->last_err" is
"itoa_copied" into "new_line". Else, "value" points to the correct value in
"datas->envp" via "find_value". Then, all the chars of value are copied into
"new_line", *pos[0] is incremented by as many chars as replaced, *pos[1] is
incremented by as many chars as copied into it by "ft_strlcpy". */
static void	exp_variable(char *line, char *new_line, int pos[2], t_data *datas)
{
	char	*value;

	value = NULL;
	if (ft_strncmp(&line[pos[0]], "$?", 2) == 0)
	{
		ft_itoa_copy(&new_line[pos[1]], datas->last_err);
		pos[1] += ft_nb_len(datas->last_err);
	}
	else if (chars_to_replace(&line[pos[0]]) != 0)
	{
		value = find_value(&line[pos[0]], datas);
		if (value != NULL)
			pos[1] += ft_strlcpy(&new_line[pos[1]], value, 
					ft_strlen(value) + 1);
	}
	pos[0] += chars_to_replace(&line[pos[0]]);
}

/* If the char encountered is not a '$' or if it is but no characters need to be
replaced (because of the following char or because of quotes), that function is
called. It just copies the current char into the new string new_line, marks that
char 0 (not expanded from an env var) into "data->exp_tab" and updates the
position counters. */
static void	add_char(char *line, char *new_line, int pos[2])
{
	new_line[pos[1]] = line[pos[0]];
	pos[0]++;
	pos[1]++;
}

/* Creates the equivalent of "data->line" with env vars expanded. Allocates
"find_size" + 1 bytes to the string "new_line", then copies every char of
"data->line" into "new_line" except when a '$' is encountered and
"chars_to_replace" shows that at least one char need to be replaced. Pos[0] is
the position counter of "*line", pos[1] is the position counter "new_line". */
int	env_var_exp_heredoc(t_data *data, t_io *io)
{
	char	*new_line;
	int		pos[2];

	if (io->is_in_quotes == TRUE)
		return (SUCCES);
	new_line = (char *)ft_calloc(find_size(data->line, data) + 1,
			sizeof(char));
	if (new_line == NULL)
		return (ft_error(errno, NULL, NULL, data));
	pos[0] = 0;
	pos[1] = 0;
	while ((data->line)[pos[0]])
	{
		if ((data->line)[pos[0]] == '$'
			&& chars_to_replace(&(data->line)[pos[0]]) != 0)
			exp_variable(data->line, new_line, pos, data);
		else
			add_char(data->line, new_line, pos);
	}
	ft_free((void **)&data->line);
	data->line = new_line;
	return (SUCCES);
}
