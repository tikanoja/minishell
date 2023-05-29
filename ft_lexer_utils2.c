#include "minishell.h"

int	check_terminator(char *str, int *len)
{
	if (str[(*len)] == '\0')
	{
		(*len)--;
		return (1);
	}
	return (0);
}

int handle_quotes(char *str, char quote, int start)
{
	int len;
	int quotes;

	init_handle_quotes(&len, &quotes, &start);
	while(1)
	{
		if (check_terminator(str, &len) == 1)
			break;
		else if (quotes % 2 == 0 && check_token_end(&str[len]) > 0)
			return (len);
		else if (str[len] == quote)
		{
			quotes++;
			if (check_token_end(&str[len + 1]) > 0 && quotes % 2 == 0)
				break ;
			else if (str[len + 1] == '\'' || str[len + 1] == '\"')
			{
				found_another_quote(&quote, str, &quotes, &len);
				continue ;
			}
		}
		len++;
	}
	return (len + 1);
}