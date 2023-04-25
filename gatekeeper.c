
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
	//ft_strlcpy(new_str, string, len - 1);
	new_str = string;
	new_str[len] = c;
	new_str[len + 1] = '\0';
	//free (string);
	//free(string);
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
	if(check_for_dollar(current->value) == 1)
	{
		while(i < len)
		{
			if(current->value[i] == '\'' && flag == 0)
				flag = 1;
			else if(current->value[i] == '\'' && flag == 1)
				flag = 0;
			if(current->value[i] == '$' && flag == 0)
			{
				i++;
				while (check_dollar_end(current->value[i]) == 0)
				{
					env = char_join(env, current->value[i]);
					printf("char is loop is %c\nand env is %s\n",current->value[i], env);
					i++;
				}
				env = getenv(env);
				if(env)
				{
					printf("this happens twice");
					new_value = ft_strjoin(new_value, env);
				}
				printf("new value at point %d is %s and char is %c\n", i, new_value,current->value[i]);
				//ft_bzero(env, ft_strlen(env));
			}
			else 
			{
				new_value = char_join(new_value, current->value[i]);
				i++;
			}
		}
		current->value = new_value;
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

	flag = 0;
	i = 0;
	j = 0;
	env = malloc(1);
	new_value = malloc(1);
	while(current->argc > j)
	{
		i = 0;
		printf("we in args");
		len = ft_strlen(current->args[j]);
		if(check_for_dollar(current->args[j]) == 1)
		{
			while(i < len)
			{
				if(current->args[j][i] == '\'' && flag == 0)
					flag = 1;
				else if(current->args[j][i] == '\'' && flag == 1)
					flag = 0;
				if(current->args[j][i] == '$' && flag == 0)
				{
					i++;
					while (check_dollar_end(current->args[j][i]) == 0)
					{
						env = char_join(env, current->args[j][i]);
						i++;
					}
					//i--;
					env = getenv(env);
					if(env)
						new_value = ft_strjoin(new_value, env);
					//ft_bzero(env, ft_strlen(env));
				}
				else
				{
					new_value = char_join(new_value, current->args[j][i]);
					i++;
				}
			}
			current->args[j] = new_value;
		}
		j++;
	}
}

void expand_envs(t_list *head)
{
	t_list *current;

	current = head;
	while(current)
	{
		check_value_for_dollar(current);
		check_args_for_dollar(current);
		current = current->next;
	}
}