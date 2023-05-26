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

int ft_env(t_list *current)
{
	int i;

	i = 0;
	if (current->args)
	{
		if (access(current->args[0], F_OK) == 0)
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(current->args[0], STDERR_FILENO);
			ft_putstr_fd(": Premission denied\n", STDERR_FILENO);
			return (126);          
		}
		else
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(current->args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (127);               
		}
	}
	while(envcpy[i])
	{
		if(ft_strchr(envcpy[i], '='))
			printf("%s\n", envcpy[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int ft_unsetenv(t_list *current)
{
	int index;
	int row_count;
	int len;
	char **new_env;
	int i;
	int j;
	int k;
	char *key;

	k = 0;
	while(current->args[k])
	{
		key = ft_strdup(current->args[k]);
		index = 0;
		row_count = 0;
		len = ft_strlen(key);
		i = 0;
		j = 0;
		while(index < len)
		{
			if(check_key_chars(key[index], index) == 0)
			{
				ft_putstr_fd("'", STDERR_FILENO);
				ft_putstr_fd(key, STDERR_FILENO);
				ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
				return (1);
			}
			index++;
		}
		index = -1;
		while (envcpy[row_count])
		{
			if (ft_strncmp(envcpy[row_count], key, len - 1) == 0 && (envcpy[row_count][len] == '=' || envcpy[row_count][len] == '\0'))
			{
				index = row_count;
			}
			row_count++;
		}
		if (index == -1)
			return (0);
		new_env = ft_calloc(row_count, sizeof(char *));
		while (envcpy[i])
		{
			if (i != index)
			{
				new_env[j] = ft_strdup(envcpy[i]);
				j++;
			}
			free(envcpy[i]);
			i++;
		}
		new_env[j] = NULL;
		free(envcpy);
		envcpy = NULL;
		envcpy = new_env;
		free(key);
		k++;
	}
	return (0);
}

