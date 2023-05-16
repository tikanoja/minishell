#include "minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *char_join(char *string, char c)
{
    size_t len = ft_strlen(string);
    char *new_str = ft_calloc(len + 2, sizeof(char));
    if (!new_str)
	{
        // handle allocation error
        exit(1);
    }
    ft_strcpy(new_str, string);
    new_str[len] = c;
    new_str[len + 1] = '\0';
	free(string);
    return (new_str);
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
	dup = ft_calloc(len + 1, sizeof(char));
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