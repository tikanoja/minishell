
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
		//printf("str c is %c\n", str[i]);
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
			exit(printf("wrong amount of quotes")); //handle error
		return (1);
	}
	else if (double_quote == 0 && single_quote > 0)
	{
		if (single_quote % 2 != 0)
			exit(printf("wrong amount of quotes")); //handle error
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

void	gatekeeper(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		if (current->value)
			check_value_for_dollar(current);
		if (current->args)
			check_args_for_dollar(current);
		if(current->value)
			open_quotes(current);
		current = current->next;
	}
}
