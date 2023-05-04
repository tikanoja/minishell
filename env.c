#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char **env;
    size_t namelen;
	char *equals;

    env = envcpy;
    namelen = 0;
	while (*env != NULL)
    {
		equals = ft_strchr(*env, '=');
		if (equals != NULL)
        {
			namelen = equals - *env;
			if (ft_strncmp(name, *env, namelen) == 0 && name[namelen] == '\0')
				return (equals + 1);
		}
		env++;
	}
	return (NULL);
}

void	ft_env(void)
{
	int i;

	i = 0;
	while(envcpy[i])
	{
		printf("%s\n", envcpy[i]);
		i++;
	}
}

void	ft_setenv(char *value)
{
	char 	**temp;
	char	**new_env;
	char	**valuepair;
	int		i;
	int		row_count;
	int		len;
	int		flag;
	int		j;

	temp = envcpy;
	i = 0;
	row_count = 0;
	flag = 0;
	j = 0;
	if (ft_strchr(value, '=') == NULL)
	{
		//handle error
		return ;
	}
	valuepair = ft_split(value, '=');
	len = ft_strlen(valuepair[0]);
	while(temp[row_count])
		row_count++;
	if(ft_strncmp(valuepair[0], "_\0", 2) == 0)
	{
		envcpy[row_count - 1] = ft_strdup(value);
		return ;
	}
	new_env = (char **)malloc(sizeof(char *) * (row_count + 2));
	while(i < row_count - 1)
	{
		if(!flag && ft_strncmp(temp[i], valuepair[0], len) == 0 && temp[i][len] == '=')
		{
			new_env[i] = ft_strdup(value);
			flag = 1;
		}
		else
			new_env[i] = ft_strdup(temp[i]);
		i++;
	}
	if (flag == 0)
	{
		new_env[i] = ft_strdup(value);
		j = i + 1;
	}
	else
		j = i;
	//new_env[i++] = "\0";
	new_env[j] = ft_strdup(temp[i]);
	envcpy = new_env;
	free(temp); //pitääkö vapauttaa koko sisältö
	free(valuepair);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void ft_unsetenv(char *key)
{
    int index;
    int row_count;
	int len;

	index = -1;
	row_count = 0;
	len = ft_strlen(key);
    while (envcpy[row_count])
    {
        printf("value is %d\n", ft_strncmp(envcpy[row_count], key, len));
        if (ft_strncmp(envcpy[row_count], key, len - 1) == 0 && envcpy[row_count][len] == '=')
        {
			printf("we herer\n");
            index = row_count;
            break;
        }
        row_count++;
    }
    if (index == -1)
        return;
    free(envcpy[index]);

    char **new_env = (char **)malloc(sizeof(char *) * row_count);
    int i = 0;
    int j = 0;
    while (envcpy[i])
    {
        if (i != index)
            new_env[j++] = ft_strdup(envcpy[i]);
        i++;
    }
    new_env[j] = NULL;

    free(envcpy);
    envcpy = new_env;
}