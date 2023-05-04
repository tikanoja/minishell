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

	temp = envcpy;
	i = 0;
	row_count = 0;
	flag = 0;
	if (ft_strchr(value, '=') == NULL)
	{
		//handle error
		return ;
	}
	valuepair = ft_split(value, '=');
	len = ft_strlen(valuepair[0]);
	while(temp[row_count])
		row_count++;
	new_env = (char **)malloc(sizeof(char *) * (row_count + 2));
	while(i < row_count)
	{
		printf("temp is %c\n",temp[i][len]);
		if(ft_strncmp(temp[i], valuepair[0], len) == 0 && temp[i][len] == '=')
		{
			new_env[i] = ft_strdup(value);
			flag = 1;
		}
		else
			new_env[i] = ft_strdup(temp[i]);
		i++;
	}
	if (flag == 0)
		new_env[i] = ft_strdup(value);
	//new_env[i++] = "\0";
	envcpy = new_env;
	free(temp); //pitääkö vapauttaa koko sisältö
	free(valuepair);
}

// void	ft_unsetenv(char *value)
// {
// 	char 	**temp;
// 	char	**new_env;
// 	int		i;
// 	int		j;
// 	int		row_count;
// 	int		len;

// 	temp = envcpy;
// 	i = 0;
// 	j = 0;
// 	row_count = 0;
// 	len = ft_strlen(value);
// 	while(temp[row_count])
// 		row_count++;
// 	new_env = (char **)malloc(sizeof(char *) * (row_count));
// 	while(i < row_count)
// 	{
// 		printf("value from count %d\n",ft_strncmp(temp[i], value, len));
// 		if(ft_strncmp(temp[i], value, len) == 0 && temp[i][len] == '=')
// 			i++;
// 		new_env[j] = ft_strdup(temp[i]);
// 		i++;
// 		j++;
// 	}
// 	//new_env[i++] = "\0";
// 	envcpy = new_env;
// 	free(temp); //pitääkö vapauttaa koko sisältö
// }
