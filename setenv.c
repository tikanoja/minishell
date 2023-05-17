#include "minishell.h"

int check_key_chars(char c, int flag)
{
	if(c >= '0' && c <= '9' && flag)
		return(1);
	else if (c >= 'a' && c <= 'z')
		return(1);
	else if (c >= 'A' && c <= 'Z')
		return(1);
	else if (c == '_')
		return(1);
	return (0);
}

int		is_valid_key(char *key)
{
	int i;

	i = 0;
	while(key[i])
	{
		if(!check_key_chars(key[i], i))
			return(0);
		i++;
	}
	return (1);
}

char **allocate_new_env(size_t size)
{
    return (char **)ft_calloc((size + 2), sizeof(char *));
}

void free_setenv(char **env)
{
    size_t i;
    
    i = 0;
    if (env == NULL)
        return ;
    while (env[i] != NULL) {
        free(env[i]);
        i++;
    }
    free(env);
}

char **copy_env(char **env)
{
    size_t size;
    size_t i;
    char **new_env;
    
    i = 0;
    size = 0;
    while (env[size] != NULL)
        size++;
    new_env = allocate_new_env(size);
    while(i < size)
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    return (new_env);
}

// void set_env_value(char **env, const char *key, const char *value)
// {
//     size_t key_len;
//     size_t env_index;
//     int found;
//     size_t size;

//     key_len = ft_strlen(key);
//     env_index = 0;
//     found = 0;
//     while (env[env_index] != NULL)
//     {
//         if (ft_strncmp(env[env_index], key, key_len) == 0 &&\
//         (env[env_index][key_len] == '=' || env[env_index][key_len] == '\0'))
//         {
//             free(env[env_index]);
//             env[env_index] = ft_strdup(value);
//             found = 1;
//             break;
//         }
//         env_index++;
//     }
//     if (!found)
//     {
//         size = env_index + 1;
//         env[size] = ft_strdup(value);
//         env[size + 1] = NULL;
//     }
//     // free(envcpy);
//     // envcpy = env;
//     // for(int i = 0; envcpy[i]; i++)
//     //     printf("%s\n", envcpy[i]);
// }
void set_env_value(char **env, const char *key, const char *value)
{
    size_t key_len;
    size_t env_index;
    int found;
    size_t size;

    key_len = ft_strlen(key);
    env_index = 0;
    found = 0;
    while (env[env_index] != NULL)
    {
        if (ft_strncmp(env[env_index], key, key_len) == 0 &&\
            (env[env_index][key_len] == '=' || env[env_index][key_len] == '\0'))
        {
            free(env[env_index]);
            env[env_index] = ft_strdup(value);
            found = 1;
            break;
        }
        env_index++;
    }
    if (!found)
    {
        size = env_index;
        env[size] = ft_strdup(value);
        env[size + 1] = NULL;
    }
    free_setenv(envcpy);
    envcpy = env;  // Update the global environment variable with the new array
}
void free_valuepair(char **valuepair)
{
    int i;

    i = 0;
    while(valuepair[i])
    {
        free(valuepair[i]);
        i++;
    }
    free(valuepair);
}

void ft_setenv(const char *value)
{
    //char **temp;
    char **valuepair;
    char **new_env;
    size_t row_count;

    //temp = envcpy;
    valuepair = NULL;
    valuepair = (char **)malloc(2 * sizeof(char *));
    valuepair = ft_split(value, '=');
    row_count = 0;
    if (value == NULL)
        return;
    if (!is_valid_key(valuepair[0]))
    {
        printf("'%s' : not a valid identifier", value);
        free(valuepair);
        return;
    }
    while (envcpy[row_count] != NULL)
        row_count++;
    if (ft_strncmp(valuepair[0], "_\0", 2) == 0)
    {
        envcpy[row_count - 1] = ft_strdup(value);
        free_valuepair(valuepair);
        return;
    }
    new_env = copy_env(envcpy);
    for (int i = 0; new_env[i]; i++)
    {
        printf("%s\n", new_env[i]);
    }
    set_env_value(new_env, valuepair[0], value);
    free_valuepair(valuepair);
    // printf("we here\n");
    // //envcpy = new_env;  // Update the global environment variable
    // printf("we here again\n");
}
