#include "minishell.h"

int check_dollar_end(char c)
{
	//printf("char c is %d\n", c);
	if(c == '\'' || c == '\"' || c == '<' || c == '>') 
		return (1);
	else if (c == '|' || c == '$' || c == '\0')
		return (1);
	else if (is_it_whitespace(c) == 1)
		return (1);
	return (0);
}

int is_valid_env_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int get_env_len(char *str)
{
	int len;
	int i;
	
	len = 0;
	i = 1; // start from 1 to skip the $ character
	while (str[i] != '\0' && is_valid_env_char(str[i])) {
		len++;
		i++;
	}
	return (len);
}
char	*ft_strjoin_oe(char *s1, char *s2)
{
	char	*ns;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	if (s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ns = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	i = 0;
	j = 0;
	if (!ns)
		return (NULL);
	while (i < s1_len)
		ns[j++] = s1[i++];
	i = 0;
	while (i < s2_len)
		ns[j++] = s2[i++];
	free(s1);
	ns[j] = '\0';
	return (ns);
}
void handle_single_quotes(char c, int *flag)
{
	if (c == '\'' && *flag == 0)
		*flag = 1;
	else if (c == '\'' && *flag == 1)
		*flag = 0;
}

int check_for_quote_dollar(char *str)
{
	if (ft_strncmp(str, "\"$\"", 4) == 0)
		return (0);
	return (1);
}


void check_value_for_dollar(t_list *current, int status)
{
	int		flag;
	int		len;
	int		i;
	char	*env;
	char	*new_value;
	char	*buffer;
	char	quote_type;

	flag = 0;
	len = ft_strlen(current->value);
	i = 0;
	if (check_for_dollar(current->value) == 1 && check_for_quote_dollar(current->value) == 1)
	{
		new_value = ft_calloc(1, sizeof(char));
		while (i < len)
		{
			if (current->value[i] == '\"' && flag != 1)
				{
					if (flag == 0)
						flag = 2;
					else
						flag = 0;
				}
			if (flag == 0)
				handle_single_quotes(current->value[i], &flag);
			if (current->value[i] == '$' && current->value[i+1] == '?' && flag == 0)
				{
					buffer = ft_itoa(status);
					new_value = ft_strjoin(new_value, buffer);
					free(buffer);
					i+=2;
				}
			if (current->value[i] == '$' && current->value[i+1] != '\"' && current->value[i+1] != '\'' &&  (flag == 0 || flag == 2))
			{
				i++;
				env = ft_strndup(current->value + i, get_env_len(current->value + i));
				if (ft_getenv(env))
					new_value = ft_strjoin_oe(new_value, ft_getenv(env));
				i += ft_strlen(env);
				free(env);
				env = NULL;
			}
			else if (current->value[i] == '$' && (current->value[i+1] == '\"' || current->value[i+1] == '\'') && (flag == 0 || flag == 2))
			{
				quote_type = current->value[i+1];
				i += 2;
				while(current->value[i] != quote_type)
				{
					new_value = char_join(new_value, current->value[i], current);
					i++;
				}
				i++;
			}
			else
			{
				new_value = char_join(new_value, current->value[i], current);
				i++;
			}
		}
		free(current->value);
		if(*new_value == '\0')
			new_value = NULL;
		current->value = new_value;
		if(current->value == NULL)
			current->execflag = 1;
		if (env)
			free(env);
	}
}


void check_args_for_dollar(t_list *current, int status)
{
	int		flag;
	int		len;
	int		i;
	int		j;
	char	*env;
	char	*new_value;
	char	*buffer;
	char	quote_type;

	j = 0;
	while (j < current->argc)
	{
		flag = 0;
		i = 0;
		len = ft_strlen(current->args[j]);
		if (check_for_dollar(current->args[j]) == 1 && check_for_quote_dollar(current->args[j]) == 1)
		{
			new_value = ft_calloc(1, sizeof(char));
			while (i < len)
			{
				if(current->args[j][i] == '\"' && flag != 1)
				{
					if (flag == 0)
						flag = 2;
					else
						flag = 0;
				}
				if(flag == 0)
					handle_single_quotes(current->args[j][i], &flag);
				if (current->args[j][i] == '$' && current->args[j][i+1] == '?' && flag == 0)
				{
					buffer = ft_itoa(status);
					new_value = ft_strjoin(new_value, buffer);
					i+=2;
					free(buffer);
				}
				if (current->args[j][i] == '$' && current->args[j][i+1] != '\"' && current->args[j][i+1] != '\'' && (flag == 0 || flag == 2))
				{
					i++;
					env = ft_strndup(current->args[j] + i, get_env_len(current->args[j] + i));
					if(ft_getenv(env))
						new_value = ft_strjoin_oe(new_value, ft_getenv(env));
					i += ft_strlen(env);
					free(env);
				}
				else if (current->args[j][i] == '$' && (current->args[j][i+1] == '\"' || current->args[j][i+1] == '\'') && (flag == 0 || flag == 2))
				{
					quote_type = current->args[j][i+1];
					i += 2;
					while(current->args[j][i] != quote_type)
					{
						new_value = char_join(new_value, current->args[j][i], current);
						i++;
					}
					i++;
				}
				else
				{
					new_value = char_join(new_value, current->args[j][i], current);
					i++;
				}
			}
			free(current->args[j]);
			current->args[j] = new_value;
		}
		j++;
	}
}
