/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalet <vvalet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:52 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/06 09:30:58 by vvalet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a pointer to the value correponding to the variable name "variable".
Because of the '$', the "variable_size" is one char shorter than what needs to
be replaced, and the variable name begins at "variable[1]". The function
iterates through "data->envp" and checks if one of the key corresponds to the
variable name. If so, it returns a pointer to the first char of that key (i.e.
the first character after the '='). */
static char	*find_value(char *variable, t_data *data)
{
	int	i;
	int	variable_size;

	i = 0;
	variable_size = chars_to_replace(variable) - 1;
	variable++;
	while (data->envp[i])
	{
		if (ft_strncmp(variable, data->envp[i], variable_size) == 0
			&& data->envp[i][variable_size] == '=')
			break ;
		i++;
	}
	if (data->envp[i] && data->envp[i][variable_size] == '=')
		return (&data->envp[i][variable_size + 1]);
	else
		return (NULL);
}

/* Finds the size required for dynamic allocation of a line with expanded env
vars. To find the result, it increments the counter "size" for every char of
"line" except for the '$'. If the following char is a '?', it adds to size
the length of converted "data->last_err" via "ft_nb_len". Else, it adds to
size the length of the env var value found via "find_value", then skips the
chars until the end of the variable name. */
size_t	find_size(char *line, t_data *data)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (is_io(line, i) == FALSE && line[i] == '$'
			&& chars_to_replace(&line[i]) > 0)
		{
			if (ft_strncmp(&line[i], "$?", 2) == 0)
				size += ft_nb_len(data->last_err);
			else if (find_value(&line[i], data))
				size += ft_strlen(find_value(&line[i], data));
			i += chars_to_replace(&line[i]);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

/* If the char encountered is a '$' and at least one char needs to be replaced,
that function is called. Pos[0] is the position counter of "*line", pos[1] is
the position counter "new_l". If the next char is a '?', "data->last_err" is
"itoa_copied" into "new_l". Else, "value" points to the correct value in
"data->envp" via "find_value". Then, all the chars of value are copied into
"new_l", *pos[0] is incremented by as many chars as replaced, *pos[1] is
incremented by as many chars as copied into it by "ft_strlcpy". Finally, the
characters expanded are marked 1 (expanded from an env var) into
"data->exp_tab". */
static void	exp_variable(char *new_l, int pos[2], t_data *data)
{
	char	*value;
	int		start;

	value = NULL;
	start = pos[1];
	if (ft_strncmp(&(data->line)[pos[0]], "$?", 2) == 0)
	{
		ft_itoa_copy(&new_l[pos[1]], data->last_err);
		pos[1] += ft_nb_len(data->last_err);
	}
	else if (chars_to_replace(&(data->line)[pos[0]]) != 0)
	{
		value = find_value(&(data->line)[pos[0]], data);
		if (value != NULL)
			pos[1] += ft_strlcpy(&new_l[pos[1]], value, ft_strlen(value) + 1);
	}
	pos[0] += chars_to_replace(&(data->line)[pos[0]]);
	while (start < pos[1])
	{
		data->exp_tab[start] = 1;
		start++;
	}
}

/* If the char encountered is not a '$' or if it is but no characters need to be
replaced (because of the following char or because of quotes), that function is
called. It just copies the current char into the new string new_l, marks that
char 0 (not expanded from an env var) into "data->exp_tab" and updates the
position counters. */
static void	add_char(char *line, char *new_l, int pos[2], t_data *data)
{
	data->exp_tab[pos[1]] = 0;
	new_l[pos[1]] = line[pos[0]];
	pos[0]++;
	pos[1]++;
}

/* Creates the equivalent of "data->line" with env vars expanded. Allocates
"find_size" + 1 bytes to the string "new_l", then copies every char of
"data->line" into "new_l" except when a '$' is encountered and
"chars_to_replace" shows that at least one char need to be replaced. Pos[0] is
the position counter of "*line", pos[1] is the position counter "new_l". */
int	env_var_exp(t_data *data)
{
	char	*new_l;
	int		pos[2];
	int		in_quotes;

	new_l = (char *)ft_calloc(find_size(data->line, data) + 1,
			sizeof(char));
	if (new_l == NULL)
		return (ft_error(errno, NULL, NULL, data));
	pos[0] = 0;
	pos[1] = 0;
	in_quotes = FALSE;
	while ((data->line)[pos[0]])
	{
		in_quotes = check_quotes(&(data->line)[pos[0]], in_quotes);
		if (is_io(data->line, pos[0]) == FALSE && (data->line)[pos[0]] == '$'
			&& in_quotes != '\''
			&& chars_to_replace(&(data->line)[pos[0]]) != 0)
			exp_variable(new_l, pos, data);
		else
			add_char(data->line, new_l, pos, data);
	}
	ft_free((void **)&data->line);
	data->line = new_l;
	return (SUCCES);
}
