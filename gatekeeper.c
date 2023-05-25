
#include "minishell.h"

char *parse_quotes(char *str)
{
	int i = 0;
	char *new_string;
	char quote;
	quote = '\0';
	if (str == NULL)
		return NULL;
	new_string = NULL;
	new_string = ft_calloc(ft_strlen(str), sizeof(char));
	if (new_string == NULL)
		return NULL;
	while (str[i])
	{
		if (str[i] == '\'' && !quote)
			quote = '\'';
		else if (str[i] == '\"' && !quote)
			quote = '\"';
		else if (str[i] == quote)
			quote = '\0';
		else
			new_string[ft_strlen(new_string)] = str[i];
		i++;
	}
	free (str);
	return (new_string);
}

int	check_if_quotes(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote == 0)
			single_quote++;
		else if (str[i] == '\"' && single_quote == 0)
			double_quote++;
		i++;
	}
	if (single_quote == 0 && double_quote > 0)
	{
		if (double_quote % 2 != 0)
			return(0); //handle error
		return (1);
	}
	else if (double_quote == 0 && single_quote > 0)
	{
		if (single_quote % 2 != 0)
			return(0); //handle error
		return (1);
	}
	return (0);
}

void	open_quotes(t_list *current)
{
	int	i;

	i = 0;
	if (check_if_quotes(current->value))
		current->value = parse_quotes(current->value);
	while (i < current->argc)
	{
		if (check_if_quotes(current->args[i]))
			current->args[i] = parse_quotes(current->args[i]);
		i++;
	}
}

void	move_arg_to_value(t_list *current)
{
	free(current->value);
	current->value = ft_strdup(current->args[0]);
	free(current->args[0]);
	current->args[0] = NULL;
}

t_list	*gatekeeper(t_list *head, int status)
{
	t_list	*current;
	int		heredoc_flag;

	current = head;
	while (current)
	{
		heredoc_flag = 1;
		if (current->prev)
			heredoc_flag = ft_strncmp(current->prev->value, "<<\0", 4);
		if (current->value && heredoc_flag != 0)
			check_value_for_dollar(current, status);
		if (current->args)
			check_args_for_dollar(current, status);
		if(current->value)
			open_quotes(current);
		if (current->value && current->value[0] == '\0' && current->args && current->args[0])
			move_arg_to_value(current);
		current = current->next;
	}
	return (head);
}
