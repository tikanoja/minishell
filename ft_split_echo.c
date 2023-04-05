
// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (*ptr != (unsigned char)c)
	{
		if (*ptr == '\0')
		{
			return (NULL);
		}
		ptr++;
	}
	return ((char *)ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s1);
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int	wordlen(char *dup, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	if (dup[i] != '\0')
	{
		while (dup[i] == c && dup[i])
			i++;
		while (dup[i] != c && dup[i])
		{
			i++;
			len++;
		}
	}
	while (j < i)
	{
		dup[j] = c;
		j++;
	}
	return (len);
}

static char	**getarray(char *dup, char c, int wcount)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (arr == NULL)
		return (NULL);
	while (i < wcount)
	{
		arr[i] = (char *)malloc(sizeof(char) * (wordlen(dup, c) + 1));
		if (arr == NULL)
			return (NULL);
		i++;
	}
	return (arr);
}

static int	wordcount(char *s, char c)
{
	//int	i;
	int	wcount;

	//i = 0;
	wcount = 0;
	if (*s != c)
		wcount = 1;
	while (*s != '\0')
	{
        printf("%c", *s);
        if (*s == 34)
        {
            s++;
            if(ft_strchr(s, 34) != 0)
            {    
                while(*s != 34)
                    s++;
                s++;    
                wcount++;
            }
            else
                exit (1);
        }  
        if (*s == 39)
        {
            s++;
            if(ft_strchr(s, 39) != 0)
            {    
                while(*s != 39)
                {
                   // write(1, "HERE", 4);
                    s++;
                }
                s++;
                wcount++;
            }
            else
                exit (1);
        }    
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0')
		{
			wcount++;
			while (*s != c && *s != '\0')
				s++;
		}
		s++;
	}
	return (wcount);
}

int wcount2(char *str, char delimiter)
{
    int i;
    int j;
    int wcount;

    i = 0;
    j = 0;
    wcount = 0;
    printf("%s\n\n", str);
    if(str[i] != delimiter)
        wcount = 1;
    while(str[i])
    {
        // if(str[i] == 34)
        // {
        //     j = i + 1;
        //     while(str[j] != 34)
        //     {
        //         if(str[j] == '\0')
        //             exit(1);
        //         j++;
        //     }
        //     wcount++;
        //     i = j + 1;
        // }
        if(str[i] == delimiter && str[i + 1] == 39)
        {
            j = i + 1;
            while(str[j] != 39)
            {
                if(str[j] == '\0')
                    exit(1);
                j++;
            }
            wcount++;
            i = j;
        }
        else if (str[i] == delimiter && str[i + 1] != delimiter && str[i + 1] != 39 && str[i + 1] != '\0')
		{
			wcount++;
			while (str[i] != delimiter && str[i] != '\0')
				i++;
		}
		i++;
    }
    return (wcount);
}

static char	**fillarr(char **arr, const char *s, char c, int wcount)
{
	int		a;
	int		b;
	size_t	i;

	a = 0;
	b = 0;
	i = 0;
	while (s[i] && a <= wcount - 1)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			arr[a][b] = s[i];
			b++;
			i++;
		}
		arr[a][b] = '\0';
		a++;
		b = 0;
	}
	arr[wcount] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	char	**arr;
	char	*dup;

	if (s == NULL)
		return (NULL);
	dup = ft_strdup(s);
	wcount = wcount2(dup, c);
    printf("\n%d\n", wcount);
    free(dup);
	if (*s == '\0' || wcount == 0)
	{
		arr = (char **)malloc(sizeof(char *));
		arr[0] = 0;
		return (arr);
	}
    dup = ft_strdup(s);
	arr = getarray(dup, c, wcount);
	if (arr == NULL)
		return (NULL);
	arr = fillarr(arr, s, c, wcount);
	free(dup);
	return (arr);
}

int main()
{
    char **test = ft_split("'hello hello'   hello", ' ');
    return 0;
}
