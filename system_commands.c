#include "minishell.h"

int	findpath(char **env)
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

void	convert_to_lowercase(char *str)
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

int	variable_assign_check(char *str)
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

char	*get_path(char **patharr, char *cmd)
{
	char *tmp;
	char *pathcmd;
	int i;

	i = 0;
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

void	move_value_to_args(t_list *current)
{
	char **arr;
	int i;

	i = 0;
	arr = malloc((current->argc + 2) * sizeof(char *)); //protect
	while(current->argc > 0 && current->args[i])
	{
		arr[i + 1] = ft_strdup(current->args[i]);
		free(current->args[i]);
		i++;
	}
	arr[0] = ft_strdup(current->value);
	if (access(current->value, F_OK) != 0)
		free(current->value);
	if (current->args)
		free(current->args);
	arr[i + 1] = NULL;
	current->args = arr;
}

void	parse_system_commands(t_list *head)
{
	int i;
	char **patharr;
	t_list *current;
	int pathflag;

	pathflag = 0;
	i = findpath(envcpy);
	if (i == -1)
		pathflag = 1;
	if (pathflag != 1)
		patharr = ft_split(envcpy[i] + 5, ':'); //protect
	current = head;
	while (current)
	{
		if (current->value[0] == '\0' || current->value == NULL)
		{
			current = current->next;
			continue;
		}
		if (is_it_builtin(current->value) == 0\
		&& variable_assign_check(current->value) == 0 && slash_check(current->value) == 0)
		{
			if (pathflag == 0)
			{
				convert_to_lowercase(current->value);
				move_value_to_args(current);
				if (access(current->value, F_OK) != 0)
					current->value = get_path(patharr, current->args[0]);
				if (current->value == NULL)
					current->system_command = -1;
				else
					current->system_command = 1;
			}
			else
			{
				ft_putstr_fd("shelly: ", 2);
				ft_putstr_fd(current->value, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
		}
		current = current->next;
	}
	i = 0;
	while(patharr[i] && pathflag != 1)
	{
		free(patharr[i]);
		i++;
	}
	if(pathflag != 1)
	free(patharr);
	return ;
}
