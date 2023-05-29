#include "minishell.h"

int check_heredoc_delim(t_list *current)
{
	if (!current->next)
	{
		ft_putstr_fd("shelly: syntax error near unexpected token `newline'\n", 2);
		if (current->prev)
			current->prev->execflag = 1;
		return (1);
	}
	return (0);
}

int	is_it_quote(char c)
{
	if(c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

void	copy_and_move_ptrs(char *input_env, char *input, int *i, int *j)
{
	input_env[*j] = input[*i];
	(*i)++;
	(*j)++;
}