#include "minishell.h"

int     findpath(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp("PATH=", env[i], 5 * sizeof(char)) == 0)
            return (i);
        i++;
    }
    return (-1);
}

void    convert_to_lowercase(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32; 
        i++;
    }
}

int     variable_assign_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char *get_path(char **patharr, char *cmd)
{
    char *tmp;
    char *pathcmd;
    int i;

    i = 0;
    if (access(cmd, F_OK) == 0)
        return (cmd);
    while (patharr[i])
	{
		tmp = ft_strjoin(patharr[i], "/");
		pathcmd = ft_strjoin(tmp, cmd);
		if (access(pathcmd, F_OK) == 0)
			break ;
		else
		{
			free(tmp);
			free(pathcmd);
			i++;
		}
		if (!patharr[i])
			return (NULL);
	}
	free(tmp);
	return (pathcmd);
}

void    parse_system_commands(char **env, t_list *head)
{
    int i;
    char **patharr;
    t_list *current;

    i = findpath(env);
    if (i == -1)
        printf("path not found in env :(\n");
    patharr = ft_split(env[i] + 5, ':'); //protect
    current = head;
    while (current)
    {
        if (is_it_builtin(current->value) == 0\
        && variable_assign_check(current->value) == 0)
        {
            convert_to_lowercase(current->value);
            printf("converted: %s\n", current->value);
            current->value = get_path(patharr, current->value);
            if (current->value == NULL)
                printf("error fetching path\n");
        }
        current = current->next;
    }
    return ;
}