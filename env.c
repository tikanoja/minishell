#include "minishell.h"

char *ft_getenv(const char *name)
{
    size_t namelen;
	char **env;

    env = envcpy;
    namelen = 0;
	while (*env != NULL)
    {
		char *equals = ft_strchr(*env, '=');
		if (equals != NULL)
        {
			size_t namelen = equals - *env;
			if (ft_strncmp(name, *env, namelen) == 0 && name[namelen] == '\0') {
				return (equals + 1);
			}
		}
		env++;
	}
	return (NULL);
}
