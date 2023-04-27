
#include "minishell.h"

char	*char_join(char *string, char c)
{
	size_t len;
	char* new_str;
	 
	len = ft_strlen(string);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
	{
		//somekind of error handler?
		exit(1);
	}
	ft_strlcpy(new_str, string, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free (string);
	return (new_str);
}

int check_for_dollar(char *string)
{
	int i;

	i = 0;
	while(string[i])
	{
		if (string[i] == '$' && string[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int check_dollar_end(char c)
{
	//printf("char c is %d\n", c);
	if(c == '\'' || c == '\"' || c == '<' || c == '>' || is_it_whitespace(c) == 1 || c == '|' || c == '$' || c == '\0')
		return(1);
	return (0);
}


size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i <= n)
	{
		i++;
	}
	return (i);
}

char	*ft_strndup(const char *string, size_t n)
{
	char		*dup;
	size_t		len;
	size_t		i;

	i = 0;
	len = ft_strnlen((char *)string, n);
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	while (i < len || i <=n)
	{
		dup[i] = string[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int is_valid_env_char(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= '0' && c <= '9')
        return 1;
    if (c == '_')
        return 1;
    return 0;
}

int get_env_len(char *str)
{
    int len = 0;
    int i = 1; // start from 1 to skip the $ character

    while (str[i] != '\0' && is_valid_env_char(str[i])) {
        len++;
        i++;
    }

    return len;
}

void check_value_for_dollar(t_list *current)
{
	int flag;
	int len;
	int i;
	char *env;
	char *new_value;

	flag = 0;
	len = ft_strlen(current->value);
	i = 0;
	env = malloc(1);
	new_value = malloc(1);
	if (check_for_dollar(current->value) == 1)
	{
		while (i < len)
		{
			if (current->value[i] == '\'' && flag == 0)
				flag = 1;
			else if (current->value[i] == '\'' && flag == 1)
				flag = 0;
			if (current->value[i] == '$' && flag == 0)
			{
				i++;
				env = ft_strndup(current->value + i, get_env_len(current->value + i));
				if (getenv(env))
					new_value = ft_strjoin(new_value, getenv(env));
				i += ft_strlen(env);
				free(env);
			}
			else
			{
				new_value = char_join(new_value, current->value[i]);
				i++;
			}
		}
		//new_value[i] = '\0';
		free(current->value);
		current->value = new_value;
	}
	else
	{
		free(env);
		free(new_value);
	}
}

void check_args_for_dollar(t_list *current)
{
    int flag;
    int len;
    int i;
    int j;
    char *env;
    char *new_value;

    j = 0;
    while (j < current->argc)
    {
        flag = 0;
        i = 0;
        env = malloc(1);
        new_value = malloc(1);
        len = ft_strlen(current->args[j]);
        if (check_for_dollar(current->args[j]) == 1)
        {
            while (i < len)
            {
				//printf("new_val %s\n", new_value);
                if (current->args[j][i] == '\'' && flag == 0)
                    flag = 1;
                else if (current->args[j][i] == '\'' && flag == 1)
                    flag = 0;
                if (current->args[j][i] == '$' && flag == 0)
                {
                    i++;
                    env = ft_strndup(current->args[j] + i, get_env_len(current->args[j] + i));
					if(getenv(env))
						new_value = ft_strjoin(new_value, getenv(env));
					i += ft_strlen(env);
                    free(env);
                }
                else
                {
                    new_value = char_join(new_value, current->args[j][i]);
                    i++;
                }
            }
            free(current->args[j]);
			printf("\nthe new_val is %s\n", new_value);
            current->args[j] = new_value;
			printf("\nthe args is %s\n", current->args[j]);
        }
        else
        {
            new_value = ft_strdup(current->args[j]);
			current->args[j] = new_value;
			//free(new_value);
        }
        j++;
    }
}


char *parse_quotes(char *str)
{
    int i = 0;
    char *new_string;
    char quote;

	new_string = NULL;
	quote = '\0';
    if (str == NULL)
        return NULL;
    new_string = (char*) malloc(ft_strlen(str) + 1);
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
    return (new_string);
}

int check_if_quotes(char *str)
{
	int i;
	int double_quote;
	int single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while(str[i])
	{
		if (str[i] == '\'' && double_quote == 0)
			single_quote++;
		else if (str[i] == '\"' && single_quote == 0)
			double_quote++;
		i++;
	}
	if(single_quote == 0 && double_quote > 0)
	{
		if(double_quote % 2 != 0)
			exit(printf("wrong amount of quotes")); //handle error
		return(1);
	}
	else if(double_quote == 0 && single_quote > 0)
	{
		if(single_quote % 2 != 0)
			exit(printf("wrong amount of quotes")); //handle error
		return(1);
	}
	return (0);
}

void	open_quotes(t_list *current)
{
	int	i;

	i = 0;
	if(check_if_quotes(current->value))
		current->value = parse_quotes(current->value);
	while(i < current->argc)
	{
		if(check_if_quotes(current->args[i]))
			current->args[i] = parse_quotes(current->args[i]);
		i++;
	}
}

void gatekeeper(t_list *head)
{
	t_list *current;

	current = head;
	while(current)
	{
		if(current->value)
			check_value_for_dollar(current);
		if(current->args)
			check_args_for_dollar(current);
		open_quotes(current);
		current = current->next;
	}
}